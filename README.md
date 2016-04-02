# compiler
### Satyaki Upadhyay - 2012A7TS022P
### Rishabh Kaul - 2012A7PS002P 

This repository contains the 'Bhasha' language compiler developed as part of Compiler Construction course, BITS Pilani.


The tokens and grammar of the language is provided in the pdf.

#### lexer.c
This file contains the lexer, which generates lexemes for use by parser and other components.
#### parser.c
This file contains the code for the parser, which works on the output of the lexer and generates the parse tree. The AST is then generated from the parse tree based on some common heuristics.
#### type_checker.c
This file contains the symbol table. It stores information about various tokens (data type, point of initialization, scope, last reference etc.). This is then used for type checking.
#### assemblyCodeGenerator.c
This file contains the code which generates the .asm assembly file from the lexer output.
#### testcases_*
These are text files containing the test cases for various phases of the compiler, including lexer, parser and assembly code generation.
