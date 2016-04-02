// Group 7 - Team 1
// Satyaki Upadhyay - 2012A7PS022P
// Rishabh Kaul - 2012A7PS002P



#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 30
#define WILDCARD ("-")

typedef struct
{
  char value[1000];
  char type[20];
  int iden, line;
} token;

FILE *fp;
char b1[SIZE],b2[SIZE];
int counter=1,flag = 0,left=0,right=0,lineno = 0;

/*void getBlock()
{
  int i=0;
  char c;
  while(i < SIZE-1)
    {
      c=getc(fp);
      if(c == EOF)
      {
        if(counter == 1) b1[i] = '\0';
        else if (counter == 2) b2[i] = '\0';
        else
        {
          if(flag == 0) b1[i] = '\0';
          else b2[i] = '\0';
        }
        return fp;
      }
      else
      {
        if(counter == 1) b1[i] = c;
        else if (counter == 2) b2[i] = c;
        else
        {
          if(flag == 0) b1[i] = c;
          else b2[i] = c;
        }
        i++;
      }
    }

  b1[i] = '$';
  b2[i] = '$';
  flag = (flag++)%2;
  counter++;
  return fp;
}*/

char block[1000];
int i=0;
int flaggy = 0;
int temp = 0;

token nextToken()
{
    char c;
    int state = 0;
    while(1)
    {
      flaggy = 0;
      /*
        if(flag == 0)
        {
          strcpy(block,b1);
        }
        else
        {
          strcpy(block,b2);
        }

        if(c == '$' && flag == 0)
        {
          getBlock();
        }

        else if(c == '$' && flag == 1)
        {
          getBlock();
        }
        */
    switch(state)
      {
        printf("%c\n",c);
          case 0:
              while((block[right] == ' ') || (block[right] == '\n') || (block[right] == '\0') || (block[right] == '\t'))
              {
                if(block[right] == '\n')
                {
                  lineno++;
                }
                left++;right++;
              }
              c=block[right];
              // printf("%c\n",c);
              if(c=='`')
              {
                right++;
                /*temp = 0;
                token t;
                  strcpy(t.type,"TK_COMMENT");
                  t.iden = 13;*/
                while(block[right] != '`')
                {
                  // t.value[temp++] = block[right];
                  right++;
                }
                //t.value[temp] = '\0';
                right++;
                state=0;
                  left = right; //t.line = lineno;
                break;
              }
              if(c=='=')
              {
                state=1;right++;
                break;
              }
              if(c=='{')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_LEFT_BR");
                  t.iden = 20;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              if(c=='}')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_RIGHT_BR");
                  t.iden = 21;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              if(c=='[')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_LSQ");
                  t.iden = 7;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              if(c==']')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_RSQ");
                  t.iden = 8;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              if(c=='(')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_LPAREN");
                  t.iden = 12;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              if(c==')')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_RPAREN");
                  t.iden = 25;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              if(c==';')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_SEMICOLON");
                  t.iden = 2;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              if(c==',')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_COMMA");
                  t.iden = 11;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              if(c=='"')
              {
                right++;
                temp = 0;
              token t;
              strcpy(t.type,"TK_STRING");
              t.iden = 17;
              while((block[right] != '"'))
              {
                t.value[temp++] = block[right];
                right++;
              }
              t.value[temp] = '\0';
              t.iden = 17;
              right++;
              state = 0;
              left = right; t.line = lineno; return t;
              break;
            }
              if(c=='Y')
              {
                state=5;right++;break;
            }
            if(c=='A')
              {
                state=86;right++;break;
            }
            if(c=='P')
              {
                state=10;right++;break;
            }
            if(c=='L')
              {
                state=15;right++;break;
            }
            if(c=='D')
              {
                state=20;right++;break;
            }
            if(c=='V')
              {
                state=24;right++;break;
            }
            if(c=='N')
              {
                state=66;right++;break;
            }
            if(c=='~')
              {
                temp = 0;
              token t;
              t.value[temp++] = '-';

              state = t.iden;//dummy

              state = 114;
              right++;
              break;
            }
            if(c=='+')
              {
                state=0;
                right++;
                token t;
                  strcpy(t.type,"TK_PLUS");
                  t.iden = 33;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
            }
            if(c=='-')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_MINUS");
                  t.iden = 34;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
            }
            if(c=='*')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_MUL");
                  t.iden = 35;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
            }
            if(c=='/')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_DIV");
                  t.iden = 36;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
            }
            if(c=='K')
              {
                state=29;right++;break;
            }
            if(c=='B')
              {
                state=36;right++;break;
            }
            if(c=='S')
              {
                state=80;right++;break;
            }
            if(c=='T')
              {
                state=42;right++;break;
            }
            if(c=='M')
              {
                state=45;right++;break;
            }
            if(c=='J')
              {
                state=51;right++;break;
            }
            if(c=='!')
              {
                state=2;right++;break;
            }
            if(c=='<')
              {
                state=3;right++;break;
            }
            if(c=='>')
              {
                state=4;right++;break;
            }
            if(c=='^')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_EXP");
                  t.iden = 37;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
            }
            if(c=='%')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_MODULO");
                  t.iden = 38;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
            }
            /*if(c=='0')
              {
                temp = 0;
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_NUMBER");
                  t.value[0] = '0';
                  t.
                  t.iden = 39;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
            }*/
            if(c=='U')
              {
                state=56;right++;
                break;
            }

            if(isdigit(c))
            {
              temp = 0;
              token t;
              t.value[temp++] = c;

              state = t.iden;//dummy

              state = 113;
              right++;
              break;
            }

            if(isalpha(c))
            {
              // printf("isalpha case 0\n");
              state = 9;right++;break;
            }

            state = -1;
            break;


        case 1:
          c = block[right];
              if(c == '=')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_EQUAL");
                  t.iden = 42;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else if (isalnum(c) || c == ' ')
              {
                state=0;
                right++;
                  token t;
                // printf("Saw ASSSIGN %d\n",right);
                  strcpy(t.type,"TK_ASSIGN");
                  t.iden = 22;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }

          case 2:
            c = block[right];
              if(c == '=')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_NE");
                  t.iden = 43;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=-1;
                right++;
                break;
              }

          case 3:
            c = block[right];
              if(c == '=')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_LE");
                  t.iden = 46;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else if (c == '<')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_LAD");
                  t.iden = 4;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_LS");
                  t.iden = 44;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }

          case 4:
            c = block[right];
              if(c == '=')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_GE");
                  t.iden = 47;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else if (c == '>')
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_RAD");
                  t.iden = 5;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=0;
                right++;
                  token t;
                  strcpy(t.type,"TK_GR");
                  t.iden = 45;
                  left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
          }

        case 5:
          c = block[right];
              if(c == 'A')
              {
                state=6;
                right++;
                break;
              }
              else
              {
                state=9;
                break;
              }

          case 6:
            c = block[right];
              if(c == 'D')
              {
                state=7;
                right++;
                break;
              }
              else
              {
                state=9;
                break;
              }

          case 7:
            c = block[right];
              if(c == 'I')
              {
                state=8;
                right++;
                break;
              }
              else
              {
                state=9;
                break;
              }

          case 8:
            c=block[right];
              if(c==' '||c=='('||c=='\0'|| c=='\n')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_IF");
                t.iden = 24;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          case 9:
              while(1)
              {

                c=block[right];
                if(isalnum(c))
                {
                  right++;
                }
                else
                {
                  break;
                }
                /*else if (c == ' ' || c == '\n'|| c == '\0' || c == '(' || c == ')' || c == ';' || c == ',')
                {
                  break;
                }
                else
                {
                  state = -1;
                  flaggy = 1;
                  break;
                }*/
              }
              // if(flaggy) break;
              state=0;
              token t;
              strcpy(t.type,"TK_IDEN");
              t.iden = 10;
              for(i = left; i < right; i++)
              {
                t.value[i-left] = block[i];
              }
              t.value[i-left] = '\0';

              /*for(i = 0; t.value[i] != '\0'; i++)
              {
                printf("%c",t.value[i]);
              }*/

              /*while(block[right]==' ' || block[right]=='\n')
              {
                right++;
              }*/
              // printf("%d %d\n",left,right);

              left = right; t.line = lineno; return t;
              break;

          case 10:
            c = block[right];
              if(c == 'A')
              {
                state=11;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 11:
            c = block[right];
              if(c == 'D')
              {
                state=12;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 12:
            c = block[right];
              if(c == 'H')
              {
                state=13;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 13:
            c = block[right];
              if(c == 'O')
              {
                state=14;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 14:
            c=block[right];
              if(c==' '|| c=='\0'|| c=='\n')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_READ");
                t.iden = 31;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

        case 15:
            c = block[right];
              if(c == 'I')
              {
                state=16;
                right++;
                break;
              }
              else if(c == 'A')
              {
                state=61;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 16:
            c = block[right];
              if(c == 'K')
              {
                state=17;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 17:
            c = block[right];
              if(c == 'H')
              {
                state=18;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 18:
            c = block[right];
              if(c == 'O')
              {
                state=19;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 19:
            c=block[right];
              if(c==' '|| c=='\0'|| c=='\n' || c == '"')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_WRITE");
                t.iden = 32;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          case 20:
            c = block[right];
              if(c == 'M')
              {
                state=21;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 21:
            c = block[right];
              if(c == 'L')
              {
                state=22;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 22:
            c = block[right];
              if(c == 'V')
              {
                state=23;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 23:
            c=block[right];
              if(c==' '|| c=='\0' || c=='\n' || c==',')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_FLOAT");
                t.iden = 16;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          case 24:
            c = block[right];
              if(c == 'A')
              {
                state=25;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 25:
            c = block[right];
              if(c == 'R')
              {
                state=26;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 26:
            c = block[right];
              if(c == 'N')
              {
                state=27;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 27:
            c = block[right];
              if(c == 'A')
              {
                state=28;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 28:
            c=block[right];
              if(c==' '|| c=='\0'|| c=='\n' || c== ',')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_CHAR");
                t.iden = 18;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

        case 29:
            c = block[right];
              if(c == 'E')
              {
                state=30;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 30:
            c = block[right];
              if(c == '_')
              {
                state=31;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 31:
            c = block[right];
              if(c == 'L')
              {
                state=32;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 32:
            c = block[right];
              if(c == 'I')
              {
                state=33;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 33:
            c = block[right];
              if(c == 'Y')
              {
                state=34;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 34:
            c = block[right];
              if(c == 'E')
              {
                state=35;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 35:
            c=block[right];
              if(c==' '|| c=='('|| c=='\0'|| c=='\n')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_LOOP");
                t.iden = 27;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          case 36:
            c = block[right];
              if(c == 'A')
              {
                state=37;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 37:
            c = block[right];
              if(c == 'D')
              {
                state=38;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 38:
            c = block[right];
              if(c == 'H')
              {
                state=39;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 39:
            c = block[right];
              if(c == 'A')
              {
                state=40;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 40:
            c = block[right];
              if(c == 'T')
              {
                state=41;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 41:
            c=block[right];
              if(c==' '|| c=='\0'|| c=='\n')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_INCR");
                t.iden = 30;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          case 42:
            c = block[right];
              if(c == 'A')
              {
                state=43;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 43:
            c = block[right];
              if(c == 'K')
              {
                state=44;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 44:
            c=block[right];
              if(c==' '|| c=='\0'|| c=='\n')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_TILL");
                t.iden = 29;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          case 45:
            c = block[right];
              if(c == 'U')
              {
                state=46;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 46:
            c = block[right];
              if(c == 'K')
              {
                state=47;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 47:
            c = block[right];
              if(c == 'H')
              {
                state=48;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 48:
            c = block[right];
              if(c == 'Y')
              {
                state=49;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 49:
            c = block[right];
              if(c == 'A')
              {
                state=50;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 50:
            c=block[right];
              if(c==' '|| c=='\0'|| c=='\n'|| c=='<')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_MAIN");
                t.iden = 3;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          case 51:
            c = block[right];
              if(c == 'A')
              {
                state=52;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 52:
            c = block[right];
              if(c == 'A')
              {
                state=53;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 53:
            c = block[right];
              if(c == 'R')
              {
                state=54;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 54:
            c = block[right];
              if(c == 'I')
              {
                state=55;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 55:
            c=block[right];
              if(c==' '|| c=='\0' || c == '\t' || c=='\n'|| c==';')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_CONTINUE");
                t.iden = 14;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          case 56:
            c = block[right];
              if(c == 'L')
              {
                state=57;
                right++;
                printf("Saw L\n");
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

        case 57:
            c = block[right];
              if(c == 'T')
              {
                state=58;
                right++;
                printf("Saw T\n");
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 58:
            c = block[right];
              if(c == 'A')
              {
                state=59;
                right++;
                printf("Saw A %d\n",right);
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 59:
            c=block[right];
              if(c==' '|| c=='\0'|| c=='\n'|| c=='(')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_REVERSE");
                t.iden = 48;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                // printf("Saw ULTA\n");
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          /*case 60:
            c = block[right];
              if(c == 'A')
              {
                state=61;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }*/

          case 61:
            c = block[right];
              if(c == 'M')
              {
                state=62;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 62:
            c = block[right];
              if(c == 'B')
              {
                state=63;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 63:
            c = block[right];
              if(c == 'A')
              {
                state=64;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 64:
            c = block[right];
              if(c == 'I')
              {
                state=65;
                right++;
                break;
              }
              else
              {
                state=9;
                right++;
                break;
              }

          case 65:
            c=block[right];
              if(c==' '|| c=='\0'|| c=='\n'|| c=='(')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_LENGTH");
                t.iden = 49;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          case 66:
            c = block[right];
              if(c == 'A')
              {
                state=67;
                right++;
                break;
              }
              else if(c == 'I')
              {
                state=75;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 67:
            c = block[right];
              if(c == 'M')
              {
                state=68;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 68:
            c = block[right];
              if(c == 'A')
              {
                state=69;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 69:
            c = block[right];
              if(c == 'S')
              {
                state=70;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 70:
            c = block[right];
              if(c == 'K')
              {
                state=71;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 71:
            c = block[right];
              if(c == 'A')
              {
                state=73;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          /*case 72:
            c = block[right];
              if(c == 'A')
              {
                state=73;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }*/

          case 73:
            c = block[right];
              if(c == 'R')
              {
                state=74;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 74:
            c=block[right];
              if(c==' '|| c=='\0' || c == '\t' || c=='\n'|| c==';')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_HELLO");
                t.iden = 1;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          case 75:
            c = block[right];
              if(c == 'K')
              {
                state=76;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 76:
            c = block[right];
              if(c == 'A')
              {
                state=77;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

      case 77:
            c = block[right];
              if(c == 'A')
              {
                state=78;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 78:
            c = block[right];
              if(c == 'S')
              {
                state=79;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 79:
            c=block[right];
              if(c==' '|| c=='\0' || c == '\t' || c=='\n'|| c==';')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_BREAK");
                t.iden = 23;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          case 80:
            c = block[right];
              if(c == 'A')
              {
                state=81;
                right++;
                break;
              }
              if(c == 'E')
              {
                state=85;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 81:
            c = block[right];
              if(c == 'T')
              {
                state=82;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 82:
            c = block[right];
              if(c == 'Y')
              {
                state=83;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 83:
            c = block[right];
              if(c == 'A')
              {
                state=84;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 84:
            c=block[right];
              if(c==' '|| c=='\0'|| c=='\n'|| c==')')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_TRUE");
                t.iden = 40;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          case 85:
            c=block[right];
              if(c==' '|| c=='\0'|| c=='\n')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_FROM");
                t.iden = 28;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          case 86:
            c = block[right];
              if(c == 'N')
              {
                state=87;
                right++;
                break;
              }
              else if(c == 'A')
              {
                state=89;
                right++;
                break;
              }
              else if(c == 'L')
              {
                state=93;
                right++;
                break;
              }
              else if(c == 'V')
              {
                state=98;
                right++;
                break;
              }
              else if(c == 'T')
              {
                state=102;
                right++;
                break;
              }
              else if(c == 'S')
              {
                state=106;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 87:
            c = block[right];
              if(c == 'K')
              {
                state=88;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 88:
            c=block[right];
              if(c==' '|| c=='\0'|| c=='\n' || c == ',')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_INT");
                t.iden = 15;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          case 89:
            c = block[right];
              if(c == 'K')
              {
                state=90;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 90:
            c = block[right];
              if(c == 'A')
              {
                state=91;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 91:
            c = block[right];
              if(c == 'R')
              {
                state=92;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 92:
            c=block[right];
              if(c==' '|| c=='\0'|| c=='\n')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_STRUC");
                t.iden = 19;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

        case 93:
            c = block[right];
              if(c == 'V')
              {
                state=94;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 94:
            c = block[right];
              if(c == 'I')
              {
                state=95;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 95:
            c = block[right];
              if(c == 'D')
              {
                state=96;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 96:
            c = block[right];
              if(c == 'A')
              {
                state=97;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 97:
            c=block[right];
              if(c==' '|| c=='\0' || c == '\t' || c=='\n'|| c==';')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_BYE");
                t.iden = 6;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          case 98:
            c = block[right];
              if(c == 'Y')
              {
                state=99;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 99:
            c = block[right];
              if(c == 'U')
              {
                state=100;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 100:
            c = block[right];
              if(c == 'H')
              {
                state=101;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 101:
            c=block[right];
              if(c==' '|| c=='\0'|| c=='\n'|| c=='{')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_ARRAY");
                t.iden = 9;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          case 102:
            c = block[right];
              if(c == 'H')
              {
                state=103;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 103:
            c = block[right];
              if(c == 'V')
              {
                state=104;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 104:
            c = block[right];
              if(c == 'A')
              {
                state=105;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }


        case 105:
            c=block[right];
              if(c==' '|| c=='\0'|| c=='\n'|| c=='<')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_ELSE");
                t.iden = 26;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          case 106:
            c = block[right];
              if(c == 'S')
              {
                state=107;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

        case 107:
            c = block[right];
              if(c == 'A')
              {
                state=108;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

        case 108:
            c = block[right];
              if(c == 'T')
              {
                state=109;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

        case 109:
            c = block[right];
              if(c == 'Y')
              {
                state=110;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }

          case 110:
            c = block[right];
              if(c == 'A')
              {
                state=111;
                right++;
                break;
              }
              else
              {
                state=9;
                // right++;
                break;
              }



        case 111:
            c=block[right];
              if(c==' '|| c=='\0'|| c=='\n'|| c==')')
              {
                state=0;
                token t;
                strcpy(t.type,"TK_FALSE");
                t.iden = 41;
                /*while(block[right]==' ' || block[right]=='\n')
                {
                  right++;
                }*/
                left = right; t.line = lineno; strcpy(t.value,WILDCARD); return t;
                break;
              }
              else
              {
                state=9;break;
              }

          /*case 112:
            printf("Unidentified Identifier.\n");
            right++;
            state = 0;
            token t1;
            strcpy(t1.type,"TK_ERROR");
            while((block[right] != ' '))
            {
              right++;
            }
            right++;
            t.line = lineno; strcpy(t.value,WILDCARD); return t;1;
            break;*/

          case 113:
            while(1)
            {
              if(isdigit(block[right]))
              {
                t.value[temp++] = block[right];
                right++;
              }
              else if(block[right] == '.')
              {
                t.value[temp++] = '.';
                right++;
                break;
              }
              else
              {
                strcpy(t.type,"TK_NUMBER");
                t.value[temp] = '\0';
                state = 0;
                t.iden = 39;
                left = right; t.line = lineno; return t;
                break;
              }
            }
            if(isdigit(block[right]))
            {
              strcpy(t.type,"TK_FLOAT");
              t.iden = 16;
              while(isdigit(block[right]))
              {
                t.value[temp++] = block[right];
                right++;
              }
            }
            else
            {
              state = -1;
              break;
            }
            t.value[temp] = '\0';
            state = 0;
            left = right; t.line = lineno; return t;
            break;

          case 114:
            if (isdigit(block[right]))
            {
              while(1)
              {
                if(isdigit(block[right]))
                {
                  t.value[temp++] = block[right];
                  right++;
                }
                else if(block[right] == '.')
                {
                  t.value[temp++] = '.';
                  right++;
                  break;
                }
                else
                {
                  strcpy(t.type,"TK_NUMBER");
                  t.value[temp] = '\0';
                  state = 0;
                  t.iden = 39;
                  left = right; t.line = lineno; return t;
                  break;
                }
              }
              if(isdigit(block[right]))
              {
                strcpy(t.type,"TK_FLOAT");
                t.iden = 16;
                while(isdigit(block[right]))
                {
                  t.value[temp++] = block[right];
                  right++;
                }
              }
              else
              {
                state = -1;
                break;
              }
              t.value[temp] = '\0';
              state = 0;
              left = right; t.line = lineno; return t;
              break;
            }
            else
            {
              state = -1;
              break;
            }

          default:
            printf("Lexical Error at Line No. %d Unidentified Character - %c\n",lineno+1,block[right]);
            exit(0);
            /*state = 0;
            right++;
            break;*/
      }
  }
  //left = right;
}


int main()
{
  fp = fopen("input.txt","r");
  freopen("lexer_output.txt","w",stdout);
  int h = 0;
  char t;
  while(1)
  {
    t = fgetc(fp);
    if(t == EOF)
    {
      break;
    }
    block[h++] = t;
  }

  block[h] = '\0';

  token tk;
  while(block[right] != '\0')
  {
    tk = nextToken();
    printf("%d %d %s\n", tk.iden, tk.line, tk.value);
  }
  return 0;
}










