%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No-terminales (backend).
	/*
	Program program;
	Expression expression;
	Factor factor;
	Constant constant;
	...
	*/

	// No-terminales (frontend).
	int program;
	int expression;
	int factor;
	int constant;

	// Terminales.
	token token;
	int integer;
	char* string;
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <token> START
%token <token> END
%token <token> FORMATION 
%token <token> FORMATIONNUMBER
%token <token> LINEUPNONUM
%token <token> LINEUP
%token <token> METADATA
%token <token> DATE
%token <token> DATESTRING 
%token <token> RESULT
%token <token> RESULTSTRING
%token <token> TEAM
%token <token> OF 
%token <token> PLAYERSFORMATION
%token <token> SUBSTITUTES
%token <token> SUBSTITUTESNONUM
%token <token> DASH
%token <token> COLON
%token <token> APOSTROPHE
%token <token> NUMBER
%token <token> YYUNDEF
%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS
%token <integer> INTEGER

// Tipos de dato para los no-terminales generados desde Bison.
%type <initial> initial
%type <info> info
%type <playerInfo> playerInfo
%type <subsitutes> subsitutes
%type <metadata> metadata
%type <matchDate> matchDate
%type <matchResult> matchResult
%type <lineup> lineup
%type <lineupNoNum> lineupNoNum
%type <playerInfoNoNum> playerInfoNoNum
%type <subsitutesNoNum> subsitutesNoNum 

// El símbolo inicial de la gramatica.
%start initial

%%

program: expression													{ $$ = ProgramGrammarAction($1); }
	;

expression: expression[left] ADD expression[right]					{ $$ = AdditionExpressionGrammarAction($left, $right); }
	| expression[left] SUB expression[right]						{ $$ = SubtractionExpressionGrammarAction($left, $right); }
	| expression[left] MUL expression[right]						{ $$ = MultiplicationExpressionGrammarAction($left, $right); }
	| expression[left] DIV expression[right]						{ $$ = DivisionExpressionGrammarAction($left, $right); }
	| factor														{ $$ = FactorExpressionGrammarAction($1); }
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS				{ $$ = ExpressionFactorGrammarAction($2); }
	| constant														{ $$ = ConstantFactorGrammarAction($1); }
	;

constant: INTEGER													{ $$ = IntegerConstantGrammarAction($1); }
	;

%%
