// Group 7 - Team 1
// Satyaki Upadhyay - 2012A7PS022P
// Rishabh Kaul - 2012A7PS002P


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define SIZE (100)
#define NUMCHAR (100)
#define EMPTY (-1)
#define TERMINAL 0
#define NONTERMINAL 1
#define MAX_CHILDREN 10


// TERMINALS
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
// #define $ 50


// NON TERMINALS
#define Namaskar 1
#define FuncDefinition 2
#define Type 3
#define Formal_parameter_list 4
#define Rem_formal_parameter_list 5
#define Statement_list 6
#define Statement 7
#define OtherStatements 8
#define Other2 9
#define BreakCont 10
#define PrimitiveTypes 11
#define Declaration_statement 12
#define AakarDeclaration 13
#define DerivedTypeDeclaration 14
#define Variable_list 15
#define Assignment_statement 16
#define Index 17
#define RHS 18
#define RHS2 19
#define Control_statement 20
#define Loop_statement 21
#define Input_output_statement 22
#define ToBeWritten 23
#define Function_statement 24
#define Actual_Parameter_list 25
#define Rem_actual_Parameter_list 26
#define ArithmeticExpr 27
#define RemArith 28
#define HighPrec 29
#define RemHighPrec 30
#define Ops 31
#define Base 32
#define Trinity 33
#define Literal 34
#define BooleanExpr 35
#define ComparableArith 36
#define BooleanOps 37
#define Inbuilt_funcs 38
#define Reverse 39
#define Length 40


char terminals[SIZE][NUMCHAR];
int t = 0;

char nonTerminals[SIZE][NUMCHAR];
int nt = 0;


void indexTerminalsAndNonterminals();	//maps all terminals and non-terminals to integers
void populateParseTable();	//fills the parse table, with the number to corresponding parameters of func()


int parseTable[SIZE][SIZE];


typedef struct
{
	char value[1000];
	char type[20];
	int iden, line;
} token;

typedef struct treeNode* TreeNode;

void func(TreeNode, int);	//stores the list of stack operations to be performed with each entry of parse table


struct treeNode{
	int type;	//terminal or non-terminal
	int iden;	//numeric index
	int c;	//number of children
	TreeNode children[MAX_CHILDREN];
	char value[1000];	//value, non-null in case of leaves (terminals)
};


typedef struct stackEle* StackEle;

struct stackEle{
	TreeNode node;
	StackEle next;
};

TreeNode root;
StackEle top;



char* printFunc(int t, int iden){

	if(t == TERMINAL)	return terminals[iden];
	return nonTerminals[iden];
}

void push(TreeNode par, int t, int val){

	TreeNode newNode = (TreeNode)malloc(sizeof(struct treeNode));
	newNode->c = 0;
	// for(i=0;i<2;i++)	n->children[i] = NULL;
	newNode->value[0] = '\0';
	newNode->type = t;
	newNode->iden = val;

	if(par != NULL)
		par->children[par->c++] = newNode;


	StackEle n = (StackEle)malloc(sizeof(StackEle));
	n->node = newNode;

	if(top == NULL){
		n->next = NULL;
		top = n;
	}
	else{

		n->next = top;
		top = n;
	}

	printf("Pushed %s\n", printFunc(newNode->type, newNode->iden));	
}


void pop(){

	TreeNode node = top->node;

	printf("Popped %s\n", printFunc(node->type, node->iden));
	top = top->next;
}


int stream_size;
token lexemeStream[1000];


// int findTerminalNumber(char str[]){

// 	for(i=1;i<=t;i++)
// 		if(!strcmp(terminals[i], str))	return i;
// 	return -1;
// }


// int findNonTerminalNumber(char str[]){

// 	for(i=1;i<=t;i++)
// 		if(!strcmp(nonTerminals[i], str))	return i;
// 	return -1;
// }





void dfs(TreeNode node){

	if(node == NULL){
		perror("Parse tree DFS reached null node.!!\n");
		return;
	}

	printf("At %s\n", printFunc(node->type, node->iden));

	int i;
	for(i=0;i<node->c;i++)
		dfs(node->children[i]);
}


int toBeTrimmed(int iden){

	if(iden == SEMICOLON || iden == LAD || iden == RAD)	return 1;
	if(iden == ASSIGN || iden == LSQ || iden == RSQ || iden == COMMA)	return 1;
	return 0;
}


void makeAST(TreeNode node){

	if(node == NULL){
		perror("AST DFS reached null node.!!\n");
		return;
	}

	printf("At %s\n", printFunc(node->type, node->iden));

	if(node->c == 1){

		printf("Deleted single child of %s.\n", printFunc(node->type, node->iden));
		int i;
		TreeNode temp = node->children[0];

		node->c = temp->c;
		for(i=0;i<temp->c;i++)
			node->children[i] = temp->children[i];

		free(temp);
	}

	TreeNode temp = (TreeNode)malloc(sizeof(TreeNode));
	temp->type = node->type;
	temp->iden = node->iden;
	strcpy(temp->value, node->value);

	temp->c = 0;
	int i;
	for(i=0;i<node->c;i++){

		TreeNode ch = node->children[i];
		if(!toBeTrimmed(ch->iden))
			temp->children[temp->c++] = ch;
	}

	if(temp->c == node->c){

		//can't be reduced
		goto lb;
	}

	//copy temp to node
	node->c = temp->c;
	for(i=0;i<node->c;i++)
		node->children[i] = temp->children[i];


	printf("Deleted some children of %s.\n", printFunc(node->type, node->iden));
	// if(temp != NULL)	free(temp);
	temp = NULL;

	printf("After deletion %d\n", node->c);
	for(i=0;i<node->c;i++)printf("%s ", printFunc(node->children[i]->type, node->children[i]->iden));printf("\n");

	lb:
	for(i=0;i<node->c;i++)
		makeAST(node->children[i]);
}



int main(){

	freopen("lexer_output.txt", "r", stdin);
	indexTerminalsAndNonterminals();
	populateParseTable();

	top = NULL;
	push(NULL, NONTERMINAL, 1);
	root = top->node;

	token t;
	while(scanf("%d%d", &t.iden, &t.line) != EOF){

		fgets(t.value, 1000, stdin);

		int len = strlen(t.value);
		t.value[len-1] = '\0';
		if(t.value[0] == '-')	t.value[0] = '\0';
		t.line++;

		lexemeStream[stream_size++] = t;
	}


	int i;
	// printf("The stream of lexemes is : \n");
	// for(i=0;i<stream_size;i++)printf("%s ", printFunc(TERMINAL, lexemeStream[i].iden));printf("\n");

	for(i=0;i<stream_size;i++){

		if(top == NULL){

			//empty stack error
			perror("Empty stack error!!!\n");
			return 0;
		}

		StackEle topOfStack = top;
		if(topOfStack->node->type == TERMINAL){

			if(lexemeStream[i].iden != topOfStack->node->iden){

				//non-matching terminals error
				perror("Non matching terminals error!!!\n");
				printf("Top of stack = %s and next lexeme = %s\n", printFunc(topOfStack->node->type, topOfStack->node->iden), printFunc(TERMINAL, lexemeStream[i].iden));
				return 0;
			}

			strcpy(topOfStack->node->value, lexemeStream[i].value);
			pop();

			continue;
		}

		int column = lexemeStream[i].iden;
		int row = topOfStack->node->iden;
		int parameter = parseTable[row][column];

		if(parameter == EMPTY){

			//empty parse table entry error

			TreeNode temp = top->node;
			printf("Empty parse table entry error when top of stack is %s and next lexeme = %s!!!\n", printFunc(temp->type, temp->iden), printFunc(TERMINAL, lexemeStream[i].iden));
			return 0;
		}

		TreeNode temp = top->node;
		pop();
		func(temp, parameter);
		i--;

	}

	printf("\nDFS of parse tree: \n");
	dfs(root);

	if(top == NULL)	printf("\nSuccessfully parsed.\n");
	else	printf("\nUnsuccessfully parsed - non empty final stack.\n");


	printf("\nAST will be generated.\n");
	makeAST(root);
	printf("\nSuccessfully made AST.\n");
	
	return 0;
}



void indexTerminalsAndNonterminals(){

	//terminals
	strcpy(terminals[++t], "tk_HELLO");
	strcpy(terminals[++t], "tk_SEMICOLON");
	strcpy(terminals[++t], "tk_MAIN");
	strcpy(terminals[++t], "tk_LAD");
	strcpy(terminals[++t], "tk_RAD");
	strcpy(terminals[++t], "tk_BYE");
	strcpy(terminals[++t], "tk_LSQ");
	strcpy(terminals[++t], "tk_RSQ");
	strcpy(terminals[++t], "tk_ARRAY");
	strcpy(terminals[++t], "tk_IDEN");
	strcpy(terminals[++t], "tk_COMMA");
	strcpy(terminals[++t], "tk_LPAREN");
	strcpy(terminals[++t], "tk_COMMENT");
	strcpy(terminals[++t], "tk_TEXT");
	strcpy(terminals[++t], "tk_INT");
	strcpy(terminals[++t], "tk_FLOAT");
	strcpy(terminals[++t], "tk_STRING");
	strcpy(terminals[++t], "tk_CHAR");
	strcpy(terminals[++t], "tk_STRUC");
	strcpy(terminals[++t], "tk_LEFT_BR");
	strcpy(terminals[++t], "tk_RIGHT_BR");
	strcpy(terminals[++t], "tk_ASSIGN");
	strcpy(terminals[++t], "tk_EXTRACT");
	strcpy(terminals[++t], "tk_IF");
	strcpy(terminals[++t], "tk_RPAREN");
	strcpy(terminals[++t], "tk_ELSE");
	strcpy(terminals[++t], "tk_LOOP");
	strcpy(terminals[++t], "tk_FROM");
	strcpy(terminals[++t], "tk_TILL");
	strcpy(terminals[++t], "tk_INCR");
	strcpy(terminals[++t], "tk_READ");
	strcpy(terminals[++t], "tk_WRITE");
	strcpy(terminals[++t], "tk_PLUS");
	strcpy(terminals[++t], "tk_MINUS");
	strcpy(terminals[++t], "tk_MUL");
	strcpy(terminals[++t], "tk_DIV");
	strcpy(terminals[++t], "tk_EXP");
	strcpy(terminals[++t], "tk_MODULO");
	strcpy(terminals[++t], "tk_NUMBER");
	strcpy(terminals[++t], "tk_TRUE");
	strcpy(terminals[++t], "tk_FALSE");
	strcpy(terminals[++t], "tk_EQUAL");
	strcpy(terminals[++t], "tk_NE");
	strcpy(terminals[++t], "tk_LS");
	strcpy(terminals[++t], "tk_GR");
	strcpy(terminals[++t], "tk_LE");
	strcpy(terminals[++t], "tk_GE");
	strcpy(terminals[++t], "tk_REVERSE");
	strcpy(terminals[++t], "tk_LENGTH");
	strcpy(terminals[++t], "$");


	//non-terminals
	strcpy(nonTerminals[++nt], "Namaskar_tag");
	strcpy(nonTerminals[++nt], "FuncDefinition");
	strcpy(nonTerminals[++nt], "Type");
	strcpy(nonTerminals[++nt], "Formal_parameter_list");
	strcpy(nonTerminals[++nt], "Rem_formal_parameter_list");
	strcpy(nonTerminals[++nt], "Statement_list");
	strcpy(nonTerminals[++nt], "Statement");
	strcpy(nonTerminals[++nt], "OtherStatements");
	strcpy(nonTerminals[++nt], "Other2");
	strcpy(nonTerminals[++nt], "CommentStatement");
	strcpy(nonTerminals[++nt], "PrimitiveTypes");
	strcpy(nonTerminals[++nt], "Declaration_statement");
	strcpy(nonTerminals[++nt], "AakarDeclaration");
	strcpy(nonTerminals[++nt], "DerivedTypeDeclaration");
	strcpy(nonTerminals[++nt], "Variable_list");
	strcpy(nonTerminals[++nt], "Assignment_statement");
	strcpy(nonTerminals[++nt], "Index");
	strcpy(nonTerminals[++nt], "RHS");
	strcpy(nonTerminals[++nt], "RHS2");
	strcpy(nonTerminals[++nt], "Control_statement");
	strcpy(nonTerminals[++nt], "Loop_statement");
	strcpy(nonTerminals[++nt], "Input_output_statement");
	strcpy(nonTerminals[++nt], "ToBeWritten");
	strcpy(nonTerminals[++nt], "Function_statement");
	strcpy(nonTerminals[++nt], "Actual_Parameter_list");
	strcpy(nonTerminals[++nt], "Rem_actual_Parameter_list");
	strcpy(nonTerminals[++nt], "ArithmeticExpr");
	strcpy(nonTerminals[++nt], "RemArith");
	strcpy(nonTerminals[++nt], "HighPrec");
	strcpy(nonTerminals[++nt], "RemHighPrec");
	strcpy(nonTerminals[++nt], "Ops");
	strcpy(nonTerminals[++nt], "Base");
	strcpy(nonTerminals[++nt], "Trinity");
	strcpy(nonTerminals[++nt], "Literal");
	strcpy(nonTerminals[++nt], "BooleanExpr");
	strcpy(nonTerminals[++nt], "ComparableArith");
	strcpy(nonTerminals[++nt], "BooleanOps");
	strcpy(nonTerminals[++nt], "Inbuilt_funcs");
	strcpy(nonTerminals[++nt], "Reverse");
	strcpy(nonTerminals[++nt], "Length");

// printf("%d\n", t);
// for(i=1;i<=t;i++){
// 	printf("%s  -  %d\n", terminals[i], i);
	
// }
// 	cout<<endl;
// for(i=1;i<=nt;i++){
// 	cout<<nonTerminals[i]<<"-"<<i<<"  ";
// 	if(i%8==0)cout<<endl;
// }cout<<endl;

}


void populateParseTable(){

	int i, j;
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++)
			parseTable[i][j] = EMPTY;

	parseTable [Namaskar] [HELLO] = 1;

	parseTable [FuncDefinition] [MAIN] = 0;

	parseTable [Type] [ARRAY] = 2;
	parseTable [Type] [INT] = 3;
	parseTable [Type] [FLOAT] = 3;
	parseTable [Type] [STRING] = 3;
	parseTable [Type] [CHAR] = 3;
	
	parseTable [Formal_parameter_list] [ARRAY] = 4;
	parseTable [Formal_parameter_list] [INT] = 4;
	parseTable [Formal_parameter_list] [FLOAT] = 4;
	parseTable [Formal_parameter_list] [STRING] = 4;
	parseTable [Formal_parameter_list] [CHAR] = 4;

	parseTable [Rem_formal_parameter_list] [RSQ] = 0;
	parseTable [Rem_formal_parameter_list] [COMMA] = 5;
	parseTable [Rem_formal_parameter_list] [RIGHT_BR] = 0;

	parseTable [Statement_list] [RAD] = 0;
	parseTable [Statement_list] [ARRAY] = 6;
	parseTable [Statement_list] [IDEN] = 6;
	parseTable [Statement_list] [COMMENT] = 6;
	parseTable [Statement_list] [CONTINUE] = 6;
	parseTable [Statement_list] [INT] = 6;
	parseTable [Statement_list] [FLOAT] = 6;
	parseTable [Statement_list] [STRING] = 6;
	parseTable [Statement_list] [CHAR] = 6;
	parseTable [Statement_list] [STRUC] = 6;
	parseTable [Statement_list] [BREAK] = 6;
	parseTable [Statement_list] [IF] = 6;
	parseTable [Statement_list] [LOOP] = 6;
	parseTable [Statement_list] [READ] = 6;
	parseTable [Statement_list] [WRITE] = 6;

	parseTable [Statement] [ARRAY] = 7;
	parseTable [Statement] [IDEN] = 8;
	parseTable [Statement] [COMMENT] = 70;
	parseTable [Statement] [CONTINUE] = 9;
	parseTable [Statement] [INT] = 7;
	parseTable [Statement] [FLOAT] = 7;
	parseTable [Statement] [STRING] = 7;
	parseTable [Statement] [CHAR] = 7;
	parseTable [Statement] [STRUC] = 7;
	parseTable [Statement] [BREAK] = 9;
	parseTable [Statement] [IF] = 10;
	parseTable [Statement] [LOOP] = 11;
	parseTable [Statement] [READ] = 12;
	parseTable [Statement] [WRITE] = 12;

	parseTable [OtherStatements] [IDEN] = 13;

	parseTable [Other2] [LSQ] = 14;
	parseTable [Other2] [LPAREN] = 15;
	parseTable [Other2] [ASSIGN] = 14;

	parseTable [BreakCont] [CONTINUE] = 16;
	parseTable [BreakCont] [BREAK] = 71;

	parseTable [PrimitiveTypes] [INT] = 17;
	parseTable [PrimitiveTypes] [FLOAT] = 18;
	parseTable [PrimitiveTypes] [STRING] = 19;
	parseTable [PrimitiveTypes] [CHAR] = 20;

	parseTable [Declaration_statement] [ARRAY] = 21;
	parseTable [Declaration_statement] [INT] = 22;
	parseTable [Declaration_statement] [FLOAT] = 22;
	parseTable [Declaration_statement] [STRING] = 22;
	parseTable [Declaration_statement] [CHAR] = 22;
	parseTable [Declaration_statement] [STRUC] = 23;

	parseTable [AakarDeclaration] [STRUC] = 24;

	parseTable [DerivedTypeDeclaration] [ARRAY] = 25;

	parseTable [Variable_list] [SEMICOLON] = 0;
	parseTable [Variable_list] [COMMA] = 26;

	parseTable [Assignment_statement] [LSQ] = 27;
	parseTable [Assignment_statement] [ASSIGN] = 27;

	parseTable [Index] [SEMICOLON] = 0;
	parseTable [Index] [LSQ] = 28;
	parseTable [Index] [ASSIGN] = 0;
	parseTable [Index] [RPAREN] = 0;
	parseTable [Index] [PLUS] = 0;
	parseTable [Index] [MINUS] = 0;
	parseTable [Index] [MUL] = 0;
	parseTable [Index] [DIV] = 0;
	parseTable [Index] [EXP] = 0;
	parseTable [Index] [MODULO] = 0;
	parseTable [Index] [EQUAL] = 0;
	parseTable [Index] [NE] = 0;
	parseTable [Index] [LS] = 0;
	parseTable [Index] [GR] = 0;
	parseTable [Index] [LE] = 0;
	parseTable [Index] [GE] = 0;

	parseTable [RHS] [IDEN] = 29;
	parseTable [RHS] [LENGTH] = 31;
	parseTable [RHS] [REVERSE] = 31;

	parseTable [RHS2] [LSQ] = 32;
	parseTable [RHS2] [IDEN] = 33;
	parseTable [RHS2] [LPAREN] = 33;
	parseTable [RHS2] [FLOAT] = 33;
	parseTable [RHS2] [NUMBER] = 33;

	parseTable [Control_statement] [IF] = 34;

	parseTable [Loop_statement] [LOOP] = 35;

	parseTable [Input_output_statement] [READ] = 36;
	parseTable [Input_output_statement] [WRITE] = 37;

	parseTable [ToBeWritten] [IDEN] = 38;
	parseTable [ToBeWritten] [STRING] = 39;

	parseTable [Function_statement] [RSQ] = 40;
	parseTable [Function_statement] [IDEN] = 40;
	parseTable [Function_statement] [NUMBER] = 40;

	parseTable [Actual_Parameter_list] [RSQ] = 0;
	parseTable [Actual_Parameter_list] [IDEN] = 41;
	parseTable [Actual_Parameter_list] [NUMBER] = 41;

	parseTable [Rem_actual_Parameter_list] [RSQ] = 0;
	parseTable [Rem_actual_Parameter_list] [COMMA] = 42;

	parseTable [ArithmeticExpr] [IDEN] = 43;
	parseTable [ArithmeticExpr] [LPAREN] = 43;
	parseTable [ArithmeticExpr] [FLOAT] = 43;
	parseTable [ArithmeticExpr] [NUMBER] = 43;

	parseTable [RemArith] [SEMICOLON] = 0;
	parseTable [RemArith] [RPAREN] = 0;
	parseTable [RemArith] [PLUS] = 44;
	parseTable [RemArith] [MINUS] = 45;
	parseTable [RemArith] [EQUAL] = 0;
	parseTable [RemArith] [NE] = 0;
	parseTable [RemArith] [LS] = 0;
	parseTable [RemArith] [GR] = 0;
	parseTable [RemArith] [LE] = 0;
	parseTable [RemArith] [GE] = 0;

	parseTable [HighPrec] [IDEN] = 46;
	parseTable [HighPrec] [LPAREN] = 46;
	parseTable [HighPrec] [FLOAT] = 46;
	parseTable [HighPrec] [NUMBER] = 46;

	parseTable [RemHighPrec] [SEMICOLON] = 0;
	parseTable [RemHighPrec] [RPAREN] = 0;
	parseTable [RemHighPrec] [PLUS] = 0;
	parseTable [RemHighPrec] [MINUS] = 0;
	parseTable [RemHighPrec] [MUL] = 47;
	parseTable [RemHighPrec] [DIV] = 47;
	parseTable [RemHighPrec] [EXP] = 47;
	parseTable [RemHighPrec] [MODULO] = 47;
	parseTable [RemHighPrec] [EQUAL] = 0;
	parseTable [RemHighPrec] [NE] = 0;
	parseTable [RemHighPrec] [LS] = 0;
	parseTable [RemHighPrec] [GR] = 0;
	parseTable [RemHighPrec] [LE] = 0;
	parseTable [RemHighPrec] [GE] = 0;

	parseTable [Ops] [MUL] = 48;
	parseTable [Ops] [DIV] = 49;
	parseTable [Ops] [EXP] = 50;
	parseTable [Ops] [MODULO] = 51;

	parseTable [Base] [IDEN] = 52;
	parseTable [Base] [LPAREN] = 53;
	parseTable [Base] [FLOAT] = 52;
	parseTable [Base] [NUMBER] = 52;

	parseTable [Trinity] [IDEN] = 54;
	parseTable [Trinity] [FLOAT] = 18;
	parseTable [Trinity] [NUMBER] = 55;

	parseTable [Literal] [IDEN] = 38;
	parseTable [Literal] [NUMBER] = 55;

	parseTable [BooleanExpr] [IDEN] = 56;
	parseTable [BooleanExpr] [LPAREN] = 56;
	parseTable [BooleanExpr] [FLOAT] = 56;
	parseTable [BooleanExpr] [NUMBER] = 56;
	parseTable [BooleanExpr] [_TRUE] = 57;
	parseTable [BooleanExpr] [_FALSE] = 58;

	parseTable [ComparableArith] [EQUAL] = 59;
	parseTable [ComparableArith] [NE] = 59;
	parseTable [ComparableArith] [LS] = 59;
	parseTable [ComparableArith] [GR] = 59;
	parseTable [ComparableArith] [LE] = 59;
	parseTable [ComparableArith] [GE] = 59;

	parseTable [BooleanOps] [EQUAL] = 60;
	parseTable [BooleanOps] [NE] = 61;
	parseTable [BooleanOps] [LS] = 62;
	parseTable [BooleanOps] [GR] = 63;
	parseTable [BooleanOps] [LE] = 64;
	parseTable [BooleanOps] [GE] = 65;

	parseTable [Inbuilt_funcs] [REVERSE] = 66;
	parseTable [Inbuilt_funcs] [LENGTH] = 67;

	parseTable [Reverse] [REVERSE] = 68;

	parseTable [Length] [LENGTH] = 69;
}


void func(TreeNode par, int n){

	if(n == -1)	return;
	switch(n){

		case 0:	break;

		case 1:	push(par, TERMINAL, SEMICOLON);
				push(par, TERMINAL, BYE);
				push(par, TERMINAL, RAD);
				push(par, NONTERMINAL, Statement_list);
				push(par, TERMINAL, LAD);
				push(par, TERMINAL, MAIN);
				push(par, NONTERMINAL, FuncDefinition);
				push(par, TERMINAL, SEMICOLON);
				push(par, TERMINAL, HELLO);
				break;

		case 2: push(par, TERMINAL, ARRAY);
				break;

		case 3:	push(par, NONTERMINAL, PrimitiveTypes);
				break;

		case 4:	push(par, NONTERMINAL, Rem_formal_parameter_list);
				push(par, TERMINAL, IDEN);
				push(par, NONTERMINAL, Type);
				break;

		case 5:	push(par, NONTERMINAL, Rem_formal_parameter_list);
				push(par, TERMINAL, IDEN);
				push(par, NONTERMINAL, Type);
				push(par, TERMINAL, COMMA);
				break;

		case 6:	push(par, NONTERMINAL, Statement_list);
				push(par, NONTERMINAL, Statement);
				break;

		case 7:	push(par, NONTERMINAL, Declaration_statement);
				break;

		case 8:	push(par, NONTERMINAL, OtherStatements);
				push(par, TERMINAL, IDEN);
				break;

		case 9:	push(par, NONTERMINAL, BreakCont);
				break;

		case 10:	push(par, NONTERMINAL, Control_statement);
					break;

		case 11:	push(par, NONTERMINAL, Loop_statement);
					break;

		case 12:	push(par, NONTERMINAL, Input_output_statement);
					break;

		case 13:	push(par, NONTERMINAL, Other2);
					push(par, TERMINAL, IDEN);
					break;

		case 14:	push(par, NONTERMINAL, Assignment_statement);
					break;

		case 15:	push(par, NONTERMINAL, Function_statement);
					push(par, TERMINAL, LPAREN);
					break;

		case 16:	push(par, TERMINAL, SEMICOLON);
					push(par, TERMINAL, CONTINUE);
					break;

		case 17:	push(par, TERMINAL, INT);
					break;

		case 18:	push(par, TERMINAL, FLOAT);
					break;

		case 19:	push(par, TERMINAL, STRING);
					break;

		case 20:	push(par, TERMINAL, CHAR);
					break;

		case 21:	push(par, NONTERMINAL, DerivedTypeDeclaration);
					break;

		case 22:	push(par, TERMINAL, SEMICOLON);
					push(par, NONTERMINAL, Variable_list);
					push(par, TERMINAL, IDEN);
					push(par, NONTERMINAL, PrimitiveTypes);
					break;

		case 23:	push(par, NONTERMINAL, AakarDeclaration);
					break;

		case 24:	push(par, TERMINAL, SEMICOLON);
					push(par, TERMINAL, RIGHT_BR);
					push(par, NONTERMINAL, Formal_parameter_list);
					push(par, TERMINAL, LEFT_BR);
					push(par, TERMINAL, IDEN);
					push(par, TERMINAL, STRUC);

		case 25:	push(par, TERMINAL, SEMICOLON);
					push(par, TERMINAL, IDEN);
					push(par, TERMINAL, RIGHT_BR);
					push(par, NONTERMINAL, Literal);
					push(par, TERMINAL, COMMA);
					push(par, NONTERMINAL, PrimitiveTypes);
					push(par, TERMINAL, LEFT_BR);
					push(par, TERMINAL, ARRAY);
					break;
	
		case 26:	push(par, NONTERMINAL, Variable_list);
					push(par, TERMINAL, IDEN);
					push(par, TERMINAL, COMMA);
					break;

		case 27:	push(par, TERMINAL, SEMICOLON);
					push(par, NONTERMINAL, RHS);
					push(par, TERMINAL, ASSIGN);
					push(par, NONTERMINAL, Index);
					break;

		case 28:	push(par, TERMINAL, RSQ);
					push(par, NONTERMINAL, Literal);
					push(par, TERMINAL, LSQ);
					break;

		case 29:	push(par, NONTERMINAL, RHS2);
					push(par, TERMINAL, IDEN);
					break;

		case 30:	push(par, TERMINAL, SEMICOLON);
					push(par, TERMINAL, IDEN);
					push(par, TERMINAL, BREAK);
					break;

		case 31:	push(par, NONTERMINAL, Inbuilt_funcs);
					break;

		case 32:	push(par, NONTERMINAL, Function_statement);
					push(par, TERMINAL, LSQ);
					break;

		case 33:	push(par, TERMINAL, SEMICOLON);
					push(par, NONTERMINAL, ArithmeticExpr);
					break;

		case 34:	push(par, TERMINAL, RAD);
					push(par, NONTERMINAL, Statement_list);
					push(par, TERMINAL, LAD);
					push(par, TERMINAL, ELSE);
					push(par, TERMINAL, RAD);
					push(par, NONTERMINAL, Statement_list);
					push(par, TERMINAL, LAD);
					push(par, TERMINAL, RPAREN);
					push(par, NONTERMINAL, BooleanExpr);
					push(par, TERMINAL, LPAREN);
					push(par, TERMINAL, IF);
					break;

		case 35:	push(par, TERMINAL, RAD);
					push(par, NONTERMINAL, Statement_list);
					push(par, TERMINAL, LAD);
					push(par, TERMINAL, RPAREN);
					push(par, NONTERMINAL, Literal);
					push(par, TERMINAL, INCR);
					push(par, TERMINAL, TILL);
					push(par, NONTERMINAL, Literal);
					push(par, TERMINAL, FROM);
					push(par, NONTERMINAL, Literal);
					push(par, TERMINAL, ASSIGN);
					push(par, TERMINAL, IDEN);
					push(par, TERMINAL, LPAREN);
					push(par, TERMINAL, LOOP);
					break;
	
		case 36:	push(par, TERMINAL, SEMICOLON);
					push(par, TERMINAL, IDEN);
					push(par, TERMINAL, READ);
					break;

		case 37:	push(par, TERMINAL, SEMICOLON);
					push(par, NONTERMINAL, ToBeWritten);
					push(par, TERMINAL, WRITE);
					break;

		case 38:	push(par, TERMINAL, IDEN);
					break;

		case 39:	push(par, TERMINAL, STRING);
					break;

		case 40:	push(par, TERMINAL, SEMICOLON);
					push(par, TERMINAL, RSQ);
					push(par, NONTERMINAL, Actual_Parameter_list);
					break;

		case 41:	push(par, NONTERMINAL, Rem_actual_Parameter_list);
					push(par, NONTERMINAL, Literal);
					break;

		case 42:	push(par, NONTERMINAL, Rem_actual_Parameter_list);
					push(par, NONTERMINAL, Literal);
					push(par, TERMINAL, COMMA);
					break;

		case 43:	push(par, NONTERMINAL, RemArith);
					push(par, NONTERMINAL, HighPrec);
					break;

		case 44:	push(par, NONTERMINAL, RemArith);
					push(par, NONTERMINAL, HighPrec);
					push(par, TERMINAL, PLUS);
					break;

		case 45:	push(par, NONTERMINAL, RemArith);
					push(par, NONTERMINAL, HighPrec);
					push(par, TERMINAL, MINUS);
					break;

		case 46:	push(par, NONTERMINAL, RemHighPrec);
					push(par, NONTERMINAL, Base);
					break;

		case 47:	push(par, NONTERMINAL, RemHighPrec);
					push(par, NONTERMINAL, Base);
					push(par, NONTERMINAL, Ops);
					break;

		case 48:	push(par, TERMINAL, MUL);
					break;

		case 49:	push(par, TERMINAL, DIV);
					break;

		case 50:	push(par, TERMINAL, EXP);
					break;

		case 51:	push(par, TERMINAL, MODULO);
					break;

		case 52:	push(par, NONTERMINAL, Trinity);
					break;

		case 53:	push(par, TERMINAL, RPAREN);
					push(par, NONTERMINAL, ArithmeticExpr);
					push(par, TERMINAL, LPAREN);
					break;

		case 54:	push(par, NONTERMINAL, Index);
					push(par, TERMINAL, IDEN);
					break;

		case 55:	push(par, TERMINAL, NUMBER);
					break;

		case 56:	push(par, NONTERMINAL, ComparableArith);
					push(par, NONTERMINAL, ArithmeticExpr);
					break;

		case 57:	push(par, TERMINAL, _TRUE);
					break;

		case 58:	push(par, TERMINAL, _FALSE);
					break;

		case 59:	push(par, NONTERMINAL, ArithmeticExpr);
					push(par, NONTERMINAL, BooleanOps);
					break;

		case 60:	push(par, TERMINAL, EQUAL);
					break;

		case 61:	push(par, TERMINAL, NE);
					break;

		case 62:	push(par, TERMINAL, LS);
					break;

		case 63:	push(par, TERMINAL, GR);
					break;

		case 64:	push(par, TERMINAL, LE);
					break;

		case 65:	push(par, TERMINAL, GE);
					break;

		case 66:	push(par, NONTERMINAL, Reverse);
					break;

		case 67:	push(par, NONTERMINAL, Length);
					break;

		case 68:	push(par, TERMINAL, SEMICOLON);
					push(par, TERMINAL, RPAREN);
					push(par, TERMINAL, IDEN);
					push(par, TERMINAL, LPAREN);
					push(par, TERMINAL, REVERSE);
					break;

		case 69:	push(par, TERMINAL, SEMICOLON);
					push(par, TERMINAL, RPAREN);
					push(par, TERMINAL, IDEN);
					push(par, TERMINAL, LPAREN);
					push(par, TERMINAL, LENGTH);
					break;

		case 70:	push(par, TERMINAL, COMMENT);
					break;

		case 71:	push(par, TERMINAL, SEMICOLON);
					push(par, TERMINAL, BREAK);
					break;
	}
}



//test 1
// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = HELLO;
// lexemeStream[stream_size++] = t;


// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = SEMICOLON;
// lexemeStream[stream_size++] = t;


// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = MAIN;
// lexemeStream[stream_size++] = t;

// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = LAD;
// lexemeStream[stream_size++] = t;

// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = INT;
// lexemeStream[stream_size++] = t;



// strcpy(t.value, "abc");	t.type[0]='\0';	t.line = 0;
// t.iden = IDEN;
// lexemeStream[stream_size++] = t;

// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = SEMICOLON;
// lexemeStream[stream_size++] = t;


// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = FLOAT;
// lexemeStream[stream_size++] = t;


// strcpy(t.value, "abc");	t.type[0]='\0';	t.line = 0;
// t.iden = IDEN;
// lexemeStream[stream_size++] = t;

// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = SEMICOLON;
// lexemeStream[stream_size++] = t;


// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = IDEN;
// lexemeStream[stream_size++] = t;


// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = IDEN;
// lexemeStream[stream_size++] = t;

// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = ASSIGN;
// lexemeStream[stream_size++] = t;



// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = IDEN;
// lexemeStream[stream_size++] = t;

// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = IDEN;
// lexemeStream[stream_size++] = t;


// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = PLUS;
// lexemeStream[stream_size++] = t;


// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = IDEN;
// lexemeStream[stream_size++] = t;


// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = SEMICOLON;
// lexemeStream[stream_size++] = t;

// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = SEMICOLON;
// lexemeStream[stream_size++] = t;


// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = RAD;
// lexemeStream[stream_size++] = t;

// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = BYE;
// lexemeStream[stream_size++] = t;

// t.value[0]='\0';	t.type[0]='\0';	t.line = 0;
// t.iden = SEMICOLON;
// lexemeStream[stream_size++] = t;










