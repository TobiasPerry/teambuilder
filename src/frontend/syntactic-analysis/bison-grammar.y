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
	int formationNumber;
	

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
%token <token> COLON
%token <token> APOSTROPHE
%token <token> NUMBER
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
%type <formationNumber> formationNumber


// El símbolo inicial de la gramatica.
%start initial

%%

initial: START info END											{ $$ = InitialAction($2); }
	;

info: team formation lineup metadata							{ $$ = InfoAction($1, $2, $3, $4 ); }
	| team formation lineupNoNum metadata						{ $$ =InfoAction($1, $2, $3, $4 ); }
	| %empty													{ $$ = Return0(); }
	;

team: TEAM STRING OF NUMBER PLAYERS		{ $$ = TeamNameAction($2, $4 ); }
	| TEAM OF NUMBER PLAYERS			{ $$ = TeamNoNameAction($3); }
	;

formation: FORMATION formationNumber							{ $$ = FormationAction($2); }
	;
formationNumber: FORMATIONNUMBER formationNumber				{ $$ = FormationNumberAction($2); }
	| FORMATIONNUMBER											{ $$ = FormationNumberFinalACtion(); }
	;

lineup: LINEUP playerInfo substitutes							{ $$ = LineupAction($2, $3); }
	;

lineupNoNum: LINEUPNONUM playerInfoNoNum substitutesNoNum 			{ $$ = LineupNoNumAction($2, $3);}
	;	

playerInfo: NUMBER COLON STRING playerInfo						{ $$ = PlayerInfoAction($1, $3, $4); }
	| NUMBER COLON STRING										{ $$ = PlayerInfoFinalAction($1, $3); }
	;

playerInfoNoNum: STRING playerInfoNoNum							{ $$ = PlayerInfoNoNumAction($2); }
	| STRING													{ $$ = PlayerInfoNoNumFinalAction($1); }
	;

substitutes: SUBSTITUTES playerInfo								{ $$ = SubstitutesAction($2); }
	| %empty													{ $$ = Return0(); }
	;

substitutesNoNum: SUBSTITUTESNONUM playerInfoNoNum				{ $$ = SubstitutesNoNumAction($2); }
	| %empty													{ $$ = Return0(); }
	;

metadata: METADATA matchDate matchResult						{ $$ = MetadataCompleteAction($2, $3); }
	| 	METADATA matchResult								    { $$ = MetadataResult($2); }
	|	METADATA matchDate										{ $$ = MetadataDate($2); }
	|   %empty												    { $$ = Return0(); }
	;

matchDate: DATE COLON DATESTRING			{ $$ = MatchDateAction($3); }
	;

matchResult: RESULT COLON APOSTROPHE RESULTSTRING APOSTROPHE	{ $$ = MatchResultAction($4); }
	;

%%
