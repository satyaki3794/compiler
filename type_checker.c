// Group 7 - Team 1
// Satyaki Upadhyay - 2012A7PS022P
// Rishabh Kaul - 2012A7PS002P


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>


#define MAX_VARIABLES 10000
#define MAX_REF 100
#define ALPHABET_SIZE 65
#define UNDEF -1

#define HELLO 1
#define SEMICOLON 2
#define MAIN 3
#define LAD 4
#define RAD 5
#define BYE 6
#define LSQ 7
#define RSQ 8
#define ARRAY 9
#define IDEN 10
#define COMMA 11
#define LPAREN 12
#define COMMENT 13
#define CONTINUE 14
#define INT 15
#define FLOAT 16
#define STRING 17
#define CHAR 18
#define STRUC 19
#define LEFT_BR 20
#define RIGHT_BR 21
#define ASSIGN 22
#define BREAK 23
#define IF 24
#define RPAREN 25
#define ELSE 26
#define LOOP 27
#define FROM 28
#define TILL 29
#define INCR 30
#define READ 31
#define WRITE 32
#define PLUS 33
#define MINUS 34
#define MUL 35
#define DIV 36
#define EXP 37
#define MODULO 38
#define NUMBER 39
#define _TRUE 40
#define _FALSE 41
#define EQUAL 42
#define NE 43
#define LS 44
#define GR 45
#define LE 46
#define GE 47
#define REVERSE 48
#define LENGTH 49
#define FUNC 50


int remap(char ch){

	if(ch >= 'A' && ch <= 'Z')	return (ch-'A'+1);
	if(ch >= 'a' && ch <= 'z')	return (26 + ch-'a'+1);
	if(ch >= '0' && ch <= '9')	return (52 + ch-'0'+1);
	return 63;	//underscore
}



typedef struct trie_node* TrieNode;

struct trie_node
{
	int value;
    TrieNode children[ALPHABET_SIZE];
};

TrieNode trieRoot;

TrieNode createNewTrieNode(){

	TrieNode newNode = (TrieNode)malloc(sizeof(struct trie_node));

	if(newNode == NULL){
		perror("Unable to create trie node!!\n");
		return NULL;
	}

	newNode->value = UNDEF;
	int i;
	for(i=0;i<ALPHABET_SIZE;i++)	newNode->children[i] = NULL;
	return newNode;
}



int totalVariables, currentScope;
int dataTypeTable[10005][12], sz[10005];


int insert(char str[]){

	int i, n = strlen(str);
	TrieNode temp = trieRoot;

	for(i=0;i<n;i++){

		int nextChar = remap(str[i]);
		if(temp->children[nextChar] == NULL)
			temp->children[nextChar] = createNewTrieNode();
		temp = temp->children[nextChar];
	}

	if(temp->value == UNDEF)	temp->value = ++totalVariables;

	// printf("%s has been inserted in trie at the scope %d and has the index %d.\n", str, currentScope, temp->value);

	return temp->value;
}



union Values{
	int a;
	char ch;
	double d;
	char str[30];
};


typedef struct{

	int declared;	//line number of declaraion
	int referenced[MAX_REF];
	int ref;	//times it hs been referenced
	int scope;	//scope 
	int data_type;	//data type of this variable
	union Values value;	//union which stores the value of this variable
	char name[100];	//variable name
} SymbolTableNode;





typedef struct symbolTableStackNode* SymbolTableStackNode;

struct symbolTableStackNode{

	SymbolTableNode node;
	SymbolTableStackNode next;
};


SymbolTableStackNode variableStack[MAX_VARIABLES];


void pushSymbolTableStackNode(int idx, int line, char name[], int dataType){

	SymbolTableStackNode newNode = (SymbolTableStackNode)malloc(sizeof(SymbolTableStackNode));

	newNode->node.declared = line;
	newNode->node.scope = currentScope;
	newNode->node.ref = 0;
	newNode->node.data_type = dataType;
	strcpy(newNode->node.name, name);

	newNode->next = variableStack[idx];
	variableStack[idx] = newNode;
	dataTypeTable[idx][sz[idx]++] = dataType;

	// printf("Variable %s %d is pushed onto stack.\n", name, dataType);
	// printf("Variable %s %d is pushed onto stack.\n", newNode->node.name, newNode->node.data_type);
}


void popSymbolTableStackNode(int idx){

	SymbolTableStackNode temp = variableStack[idx];

	if(temp == NULL){

		printf("Empty varable stack at idx = %d.\n", idx);
		return;
	}

	variableStack[idx] = variableStack[idx]->next;
	free(temp);
}


typedef struct envListNode* EnvListNode;
struct envListNode{

	int idx;
	EnvListNode next;
};


typedef struct envStackNode* EnvStackNode;
struct envStackNode{
	
	EnvListNode ev;
	EnvStackNode next;
};
EnvStackNode envTop;


void addScope();
void deleteScope();
void addVariable();
void createEnvListNode();
void destroyEnvList(EnvListNode*);


void addScope(){

	EnvStackNode newNode = (EnvStackNode)malloc(sizeof(EnvStackNode));
	newNode->ev = NULL;
	newNode->next = envTop;

	envTop = newNode;

	currentScope++;
	printf("Entered scope = %d.\n", currentScope);
}


void deleteScope(){

	if(envTop == NULL){
		perror("Empty environment stack error!!\n");
		return;
	}

	EnvListNode ev = envTop->ev;

	while(ev != NULL){

		sz[ev->idx]--;
		popSymbolTableStackNode(ev->idx);
		ev = ev->next;
	}

	destroyEnvList(&ev);

	EnvStackNode temp = envTop;
	envTop = envTop->next;
	free(temp);

	printf("Exited scope = %d.\n", currentScope);
	currentScope--;
}


void createEnvListNode(int id){

	EnvListNode newNode = (EnvListNode)malloc(sizeof(struct envListNode));
	newNode->idx = id;

	if(envTop == NULL){
		perror("Empty environment stack!!\n");
		return;
	}

	newNode->next = envTop->ev;
	envTop->ev = newNode;
}


void destroyEnvList(EnvListNode *listNode){

	EnvListNode next, curr = *listNode;

	while(curr != NULL){

		next = curr->next;
		free(curr);
		curr = next;
	}

	*listNode = NULL;
}



typedef struct
{
	char value[1000];
	char type[20];
	int iden, line;
} token;

int stream_size;
token lexemeStream[1000];
char funcName[105];
int funcParameterCount, funcParameterType[105];


void declareVariable(token, int);
void referenceVariable(token);



int isDataType(int value){

	if(value == ARRAY || value == INT || value == FLOAT)	return 1;
	if(value == CHAR || value == STRUC)	return 1;
	return 0;
}


void declareVariable(token t, int iden){

	if(envTop == NULL){
		perror("Semantic error: There is no current scope to declare a variable in.!!\n");
		return;
	}

	int idx = insert(t.value);

	SymbolTableStackNode temp = variableStack[idx];
	if(temp != NULL && temp->node.scope == currentScope){

		printf("Semantic error: Multiple declarations of %s in the same scope are not allowed.\n", t.value);
		return;
	}


	createEnvListNode(idx);
	pushSymbolTableStackNode(idx, t.line, t.value, iden);

	printf("Variable named %s has been declared at line %d.\n", t.value, t.line);

	// SymbolTableNode z = temp->node;
	// printf("declaration : %d %s %d %d %d\n", idx, z.name, z.declared, z.ref, z.data_type);
}


void referenceVariable(token t){

	if(envTop == NULL){
		perror("Semantic error: There is no current scope for the variable to be referenced in.!!\n");
		return;
	}

	int idx = insert(t.value);

	SymbolTableStackNode temp = variableStack[idx];

	if(temp == NULL){
	
		printf("Semantic error in line %d: Variable of the name : %s has not been declared earlier.!!\n", t.line, t.value);
		return;
	}

	temp->node.referenced[temp->node.ref++] = t.line;
	printf("Variable named %s has been referenced at line %d.\n", t.value, t.line);

	// SymbolTableNode z = temp->node;
	// printf("reference %d %s %d %d %d\n", idx, z.name, z.declared, z.ref, z.data_type);
}


int getDataType(token t){

	int idx = insert(t.value);
	SymbolTableStackNode temp = variableStack[idx];

	int z = dataTypeTable[idx][sz[idx]-1];
	// printf("Found variable %s %d.\n", t.value, z);
	return z;
}


int main(){

	freopen("lexer_output.txt", "r", stdin);
	trieRoot = createNewTrieNode();
	if(trieRoot == NULL){
		perror("Could not create root node!!\n");
		return 0;
	}

	envTop = NULL;
	currentScope = totalVariables = 0;
	addScope();


	token t;
	while(scanf("%d%d", &t.iden, &t.line) != EOF){

		fgets(t.value, 1000, stdin);

		int len = strlen(t.value);
		t.value[len-1] = '\0';
		if(t.value[0] == '-')	t.value[0] = '\0';
		t.line++;

		lexemeStream[stream_size++] = t;
	}

	// int zz;
	// for(zz=0;zz<stream_size;zz++)
	// 	printf("%d ", lexemeStream[zz].iden);	printf("\n");


	int i, n = stream_size, lastLineOfDeclaration = -1, lastDataTypeOfDeclaration = -1;
	int lastDataTypeOfAssignment = -1, lastLineOfAssignment = -1;
	funcName[0] = '!';	funcName[1] = '\0';
	int insideMain = 0, diff = 0;
	funcParameterCount = 0;

	for(i=0;i<n;i++){

		if(lexemeStream[i].iden == MAIN)	insideMain = 1;
		if(i == 2){

			if(lexemeStream[i].iden != MAIN){

				assert(lexemeStream[i].iden == FUNC);
				strcpy(funcName, lexemeStream[i+1].value);
			}
			i++;
			continue;
		}

		//check for recursive function calls
		if(lexemeStream[i].iden == FUNC && !insideMain){

			printf("Semantic error: Recursive function calls not allowed.\n");
			continue;
		}

		if(lexemeStream[i].iden == LSQ){
			diff++;
			continue;
		}

		if(lexemeStream[i].iden == RSQ){
			diff--;
			continue;
		}


		//store function parameter list
		if(isDataType(lexemeStream[i].iden) && diff > 0 && !insideMain){

			funcParameterType[funcParameterCount++] = lexemeStream[i].iden;
		}

		//for function calls inside main, check whether correct function name is used
		//then check for correct number and types of parameters
		if(insideMain && i > 0 && lexemeStream[i].iden == IDEN && lexemeStream[i-1].iden == FUNC){

			if(strcmp(funcName, lexemeStream[i].value) > 0)
				printf("Function named %s in line %d not declared.\n", lexemeStream[i].value, lexemeStream[i].line);

			int j, argumentCount = 0, wrongType = 0;
			for(j=i+1;j < stream_size && lexemeStream[j].iden != RSQ;j++){

				if(lexemeStream[j].iden != IDEN)	continue;

				if(argumentCount < funcParameterCount && getDataType(lexemeStream[j]) != funcParameterType[argumentCount])
					wrongType = lexemeStream[j].line;
				argumentCount++;
			}

			if(argumentCount != funcParameterCount)	printf("Incorrect number of function arguments in line %d.\n", lexemeStream[j].line);
			if(wrongType > 0)	printf("Type mismatch in function parameters in line %d.\n", wrongType);

			i = j;
			continue;
		}

		if(lexemeStream[i].iden == LAD){
			addScope();
			continue;
		}

		if(lexemeStream[i].iden == RAD){
			deleteScope();
			continue;
		}

		if(isDataType(lexemeStream[i].iden)){

			lastLineOfDeclaration = lexemeStream[i].line;
			lastDataTypeOfDeclaration = lexemeStream[i].iden;

// printf("setting lastlineOfDeclaration = %d because of %d.\n", lastLineOfDeclaration, lexemeStream[i].iden);
			continue;
		}


		if(lexemeStream[i].iden == ASSIGN){

			//line number of assignment operator
			lastLineOfAssignment = lexemeStream[i].line;
			continue;
		}


		if(lexemeStream[i].iden == IDEN){

			insert(lexemeStream[i].value);

			//check if variable is being declared or referenced
			if(lastLineOfDeclaration == lexemeStream[i].line){

				//declared
				declareVariable(lexemeStream[i], lastDataTypeOfDeclaration);
				continue;
			}

			//referenced
			referenceVariable(lexemeStream[i]);

			if(lexemeStream[i].line != lastLineOfAssignment){

				lastDataTypeOfAssignment = getDataType(lexemeStream[i]);
				continue;
			}


			if(lexemeStream[i].line == lastLineOfAssignment){

				int dataType = getDataType(lexemeStream[i]);
				if(dataType != lastDataTypeOfAssignment){

					printf("Semantic error in line %d: Type mismatch between LHS and RHS in line %d.\n", lexemeStream[i].line, lastLineOfAssignment);
				}
				continue;
			}
		}
	}

// int c = 0, cc = 0;
// EnvStackNode temp = envTop;
// while(temp != NULL){
	
// 	c++;
// 	EnvListNode ev = temp->ev;
// 	while(ev != NULL){
// 		cc++;
// 		ev = ev->next;
// 	}

// 	temp = temp->next;
// }
// printf("Total active scopes : %d and active variables = %d.\n", c, cc);
// printf("\ncheck variable stack of size = %d :\n", z);
// for(int i=0;i<z;i++){

// 	int idx = vvv[i];
// 	if(variableStack[idx] == NULL){
// 		printf("empty stack at idx = %d\n", idx);
// 		continue;
// 	}
// 	printf("idx = %d has the value = %s\n", idx, variableStack[idx]->node.name);
// }

	return 0;
}




//test 1

// token t;
// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = HELLO;
// lexemeStream[stream_size++] = t;


// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = SEMICOLON;
// lexemeStream[stream_size++] = t;


// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = FUNC;
// lexemeStream[stream_size++] = t;

// strcpy(t.value, "kaul");	t.type[0]='\0';	t.line = 1;
// t.iden = IDEN;
// lexemeStream[stream_size++] = t;


// t.value[0]='\0';	t.type[0]='\0';	t.line = 2;
// t.iden = LSQ;
// lexemeStream[stream_size++] = t;


// t.value[0]='\0';	t.type[0]='\0';	t.line = 2;
// t.iden = INT;
// lexemeStream[stream_size++] = t;



// strcpy(t.value, "a");	t.type[0]='\0';	t.line = 2;
// t.iden = IDEN;
// lexemeStream[stream_size++] = t;


// strcpy(t.value, "a");	t.type[0]='\0';	t.line = 2;
// t.iden = COMMA;
// lexemeStream[stream_size++] = t;


// t.value[0]='\0';	t.type[0]='\0';	t.line = 2;
// t.iden = FLOAT;
// lexemeStream[stream_size++] = t;



// strcpy(t.value, "b");	t.type[0]='\0';	t.line = 2;
// t.iden = IDEN;
// lexemeStream[stream_size++] = t;


// strcpy(t.value, "a");	t.type[0]='\0';	t.line = 2;
// t.iden = COMMA;
// lexemeStream[stream_size++] = t;

// t.value[0]='\0';	t.type[0]='\0';	t.line = 2;
// t.iden = INT;
// lexemeStream[stream_size++] = t;



// strcpy(t.value, "c");	t.type[0]='\0';	t.line = 2;
// t.iden = IDEN;
// lexemeStream[stream_size++] = t;



// t.value[0]='\0';	t.type[0]='\0';	t.line = 2;
// t.iden = RSQ;
// lexemeStream[stream_size++] = t;




// t.value[0]='\0';	t.type[0]='\0';	t.line = 3;
// t.iden = MAIN;
// lexemeStream[stream_size++] = t;

// t.value[0]='\0';	t.type[0]='\0';	t.line = 3;
// t.iden = LAD;
// lexemeStream[stream_size++] = t;

// t.value[0]='\0';	t.type[0]='\0';	t.line = 4;
// t.iden = INT;
// lexemeStream[stream_size++] = t;



// strcpy(t.value, "a");	t.type[0]='\0';	t.line = 4;
// t.iden = IDEN;
// lexemeStream[stream_size++] = t;

// t.value[0]='\0';	t.type[0]='\0';	t.line = 4;
// t.iden = SEMICOLON;
// lexemeStream[stream_size++] = t;


// t.value[0]='\0';	t.type[0]='\0';	t.line = 4;
// t.iden = FLOAT;
// lexemeStream[stream_size++] = t;


// strcpy(t.value, "b");	t.type[0]='\0';	t.line = 4;
// t.iden = IDEN;
// lexemeStream[stream_size++] = t;

// t.value[0]='\0';	t.type[0]='\0';	t.line = 4;
// t.iden = SEMICOLON;
// lexemeStream[stream_size++] = t;


// t.value[0]='\0';	t.type[0]='\0';	t.line = 4;
// t.iden = INT;
// lexemeStream[stream_size++] = t;


// strcpy(t.value, "c");	t.type[0]='\0';	t.line = 4;
// t.iden = IDEN;
// lexemeStream[stream_size++] = t;

// t.value[0]='\0';	t.type[0]='\0';	t.line = 4;
// t.iden = SEMICOLON;
// lexemeStream[stream_size++] = t;





// t.value[0]='\0';	t.type[0]='\0';	t.line = 5;
// t.iden = FUNC;
// lexemeStream[stream_size++] = t;

// strcpy(t.value, "kaul");	t.type[0]='\0';	t.line = 5;
// t.iden = IDEN;
// lexemeStream[stream_size++] = t;


// t.value[0]='\0';	t.type[0]='\0';	t.line = 5;
// t.iden = LSQ;
// lexemeStream[stream_size++] = t;


// strcpy(t.value, "a");	t.type[0]='\0';	t.line = 5;
// t.iden = IDEN;
// lexemeStream[stream_size++] = t;


// strcpy(t.value, "a");	t.type[0]='\0';	t.line = 5;
// t.iden = COMMA;
// lexemeStream[stream_size++] = t;



// strcpy(t.value, "b");	t.type[0]='\0';	t.line = 5;
// t.iden = IDEN;
// lexemeStream[stream_size++] = t;


// strcpy(t.value, "a");	t.type[0]='\0';	t.line = 5;
// t.iden = COMMA;
// lexemeStream[stream_size++] = t;


// strcpy(t.value, "c");	t.type[0]='\0';	t.line = 5;
// t.iden = IDEN;
// lexemeStream[stream_size++] = t;



// t.value[0]='\0';	t.type[0]='\0';	t.line = 5;
// t.iden = RSQ;
// lexemeStream[stream_size++] = t;

// t.value[0]='\0';	t.type[0]='\0';	t.line = 6;
// t.iden = RAD;
// lexemeStream[stream_size++] = t;





//test 2
// 		strcpy(t.value, "");	t.type[0]='\0';	t.line = 3;
// 		t.iden = FLOAT;
// 		lexemeStream[stream_size++] = t;

// 		strcpy(t.value, "ab");	t.type[0]='\0';	t.line = 3;
// 		t.iden = 10;
// 		lexemeStream[stream_size++] = t;

// 		strcpy(t.value, "abcsdfdf");	t.type[0]='\0';	t.line = 4;
// 		t.iden = 10;
// 		lexemeStream[stream_size++] = t;


// 		strcpy(t.value, "ab");	t.type[0]='\0';	t.line = 4;
// 		t.iden = 10;
// 		lexemeStream[stream_size++] = t;

// 		strcpy(t.value, "");	t.type[0]='\0';	t.line = 5;
// 		t.iden = LAD;
// 		lexemeStream[stream_size++] = t;


// 				strcpy(t.value, "");	t.type[0]='\0';	t.line = 3;
// 				t.iden = FLOAT;
// 				lexemeStream[stream_size++] = t;

// 				strcpy(t.value, "ab");	t.type[0]='\0';	t.line = 3;
// 				t.iden = 10;
// 				lexemeStream[stream_size++] = t;


// 		strcpy(t.value, "");	t.type[0]='\0';	t.line = 5;
// 		t.iden = RAD;
// 		lexemeStream[stream_size++] = t;

// 	strcpy(t.value, "");	t.type[0]='\0';	t.line = 6;
// 	t.iden = CHAR;
// 	lexemeStream[stream_size++] = t;

// 	strcpy(t.value, "Ab");	t.type[0]='\0';	t.line = 6;
// 	t.iden = 10;
// 	lexemeStream[stream_size++] = t;

// 	strcpy(t.value, "AB");	t.type[0]='\0';	t.line = 7;
// 	t.iden = 10;
// 	lexemeStream[stream_size++] = t;


// strcpy(t.value, "");	t.type[0]='\0';	t.line = 7;
// t.iden = RAD;
// lexemeStream[stream_size++] = t;

// strcpy(t.value, "");	t.type[0]='\0';	t.line = 8;
// t.iden = INT;
// lexemeStream[stream_size++] = t;
// strcpy(t.value, "aB");	t.type[0]='\0';	t.line = 8;
// t.iden = 10;
// lexemeStream[stream_size++] = t;


// strcpy(t.value, "");	t.type[0]='\0';	t.line = 10;
// t.iden = INT;
// lexemeStream[stream_size++] = t;

// strcpy(t.value, "AB");	t.type[0]='\0';	t.line = 10;
// t.iden = 10;
// lexemeStream[stream_size++] = t;













