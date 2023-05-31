%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No-terminales (backend).
	InitialNode * initialNode;
	InfoNode * infoNode;
	TeamNode * teamNode;
	FormationNode * formationNode;
	FormationNumberNode * formationNumberNode;
	LineupNode * lineupNode;
	PlayerInfoNode * playerInfoNode;
	SubstitutesNode * substitutesNode;
	LineupNoNumNode * lineupNoNumNode;
	PlayerInfoNoNumNode * playerInfoNoNumNode;
	SubstitutesNoNumNode * substitutesNoNumNode;
	MetadataNode * metadataNode;
	MatchDateNode * matchDateNode;
	MatchResultNode * matchResultNode;

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
%token <token> LINEUPNONUM
%token <token> LINEUP
%token <token> METADATA
%token <token> DATE
%token <token> RESULT
%token <token> OF 
%token <token> SUBSTITUTES
%token <token> SUBSTITUTESNONUM
%token <token> COLON
%token <token> APOSTROPHE
%token <token> PLAYERS
%token <token> TEAM

%token <integer> NUMBER
%token <string> DATESTRING 
%token <string> RESULTSTRING
%token <string> FORMATIONNUMBER
%token <string> STRING

// Tipos de dato para los no-terminales generados desde Bison.
%type <initialNode> initial
%type <infoNode> info
%type <playerInfoNode> playerInfo
%type <substitutesNode> substitutes
%type <metadataNode> metadata
%type <matchDateNode> matchDate
%type <matchResultNode> matchResult
%type <lineupNode> lineup
%type <lineupNoNumNode> lineupNoNum
%type <playerInfoNoNumNode> playerInfoNoNum
%type <substitutesNoNumNode> substitutesNoNum 
%type <formationNode> formation
%type <teamNode> team
%type <formationNumberNode> formationNumber


// El símbolo inicial de la gramatica.
%start initial

%%

initial: START info END											{ $$ = InitialAction($2); }
	;

info: team formation lineup metadata							{ $$ = InfoAction($1, $2, $3, $4 ); }
	| team formation lineupNoNum metadata						{ $$ = InfoNoNumAction($1, $2, $3, $4 ); }
	| %empty													{ $$ = Return0(); }
	;

team: TEAM STRING OF NUMBER PLAYERS								{ $$ = TeamNameAction($2, $4 ); }
	| TEAM OF NUMBER PLAYERS									{ $$ = TeamNoNameAction($3); }
	;

formation: FORMATION formationNumber							{ $$ = FormationAction($2); }
	;
formationNumber: FORMATIONNUMBER formationNumber				{ $$ = FormationNumberAction($1,$2); }
	| FORMATIONNUMBER											{ $$ = FormationNumberFinalAction($1); }
	;

lineup: LINEUP playerInfo substitutes							{ $$ = LineupAction($2, $3); }
	;

lineupNoNum: LINEUPNONUM playerInfoNoNum substitutesNoNum 		{ $$ = LineupNoNumAction($2, $3);}
	;	

playerInfo: NUMBER COLON STRING playerInfo						{ $$ = PlayerInfoAction($1, $3, $4); }
	| NUMBER COLON STRING										{ $$ = PlayerInfoFinalAction($1, $3); }
	;

playerInfoNoNum: STRING playerInfoNoNum							{ $$ = PlayerInfoNoNumAction($1, $2); }
	| STRING													{ $$ = PlayerInfoNoNumFinalAction($1); }
	;

substitutes: SUBSTITUTES playerInfo								{ $$ = SubstitutesAction($2); }
	| %empty													{ $$ = Return0(); }
	;

substitutesNoNum: SUBSTITUTESNONUM playerInfoNoNum				{ $$ = SubstitutesNoNumAction($2); }
	| %empty													{ $$ = Return0(); }
	;

metadata: METADATA matchDate matchResult						{ $$ = MetadataCompleteAction($2, $3); }
	| 	METADATA matchResult								    { $$ = MetadataResultAction($2); }
	|	METADATA matchDate										{ $$ = MetadataDateAction($2); }
	|   %empty												    { $$ = Return0(); }
	;

matchDate: DATE COLON DATESTRING								{ $$ = MatchDateAction($3); }
	;

matchResult: RESULT COLON APOSTROPHE RESULTSTRING APOSTROPHE	{ $$ = MatchResultAction($4); }
	;

%%
