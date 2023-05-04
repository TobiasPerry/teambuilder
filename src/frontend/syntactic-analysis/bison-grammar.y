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
	int initial;
	int info;
	int playerInfo;
	int substitutes;
	int metadata;
	int matchDate;
	int matchResult;
	int lineup;
	int lineupNoNum;
	int playerInfoNoNum;
	int substitutesNoNum;
	int team;
	int formation;
	

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
%token <token> STRING
%token <token> PLAYERS

// Tipos de dato para los no-terminales generados desde Bison.
%type <initial> initial
%type <info> info
%type <playerInfo> playerInfo
%type <substitutes> substitutes
%type <metadata> metadata
%type <matchDate> matchDate
%type <matchResult> matchResult
%type <lineup> lineup
%type <lineupNoNum> lineupNoNum
%type <playerInfoNoNum> playerInfoNoNum
%type <substitutesNoNum> substitutesNoNum 
%type <formation> formation
%type <team> team


// El símbolo inicial de la gramatica.
%start initial

%%

initial: START info END											{ $$ = InitialAction($2); }
	;

info: team formation lineup metadata							{ $$ = Return0(); }
	| team formation lineupNoNum metadata						{ $$ = Return0(); }
	| %empty													{ $$ = Return0(); }
	;

team: TEAM APOSTROPHE STRING APOSTROPHE OF NUMBER PLAYERS		{ $$ = Return0(); }
	;

formation: FORMATION FORMATIONNUMBER							{ $$ = Return0(); }
	;

lineup: LINEUP playerInfo substitutes							{ $$ = Return0(); }
	;

lineupNoNum: LINEUPNONUM playerInfoNoNum substitutesNoNum 			{ $$ = Return0();}
	;	

playerInfo: NUMBER COLON APOSTROPHE STRING APOSTROPHE playerInfo	{ $$ = Return0(); }
	| NUMBER COLON APOSTROPHE STRING APOSTROPHE						{ $$ = Return0(); }
	;

playerInfoNoNum: APOSTROPHE STRING APOSTROPHE playerInfoNoNum	{ $$ = Return0(); }
	| APOSTROPHE STRING APOSTROPHE								{ $$ = Return0(); }
	;

substitutes: SUBSTITUTES playerInfo								{ $$ = Return0(); }
	| %empty													{ $$ = Return0(); }
	;

substitutesNoNum: SUBSTITUTESNONUM playerInfoNoNum				{ $$ = Return0(); }
	| %empty													{ $$ = Return0(); }
	;

metadata: METADATA matchDate matchResult						{ $$ = Return0(); }
	;

matchDate: DATE COLON APOSTROPHE DATESTRING APOSTROPHE			{ $$ = Return0(); }
	;

matchResult: RESULT COLON APOSTROPHE RESULTSTRING APOSTROPHE	{ $$ = Return0(); }
	;



%%
