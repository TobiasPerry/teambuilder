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
	SubInfoNode * subInfoNode;
	SubInfoNoNumNode * subInfoNoNumNode;

	// No-terminales (frontend).
	int initial;
	int info;
	int playerInfo;
	//int subInfo;
	int substitutes;
	int metadata;
	int matchDate;
	int matchResult;
	int lineup;
	int lineupNoNum;
	int playerInfoNoNum;
	//int subInfoNoNum;
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
%type <formationNode> formation
%type <teamNode> team
%type <formationNumberNode> formationNumber
%type <substitutesNoNumNode> substitutesNoNum 

//agregados hoy:
%type <subInfoNoNumNode> subInfoNoNum
%type <subInfoNode> subInfo


// El símbolo inicial de la gramatica.
%start initial

%%

initial: START info END											{ $$ = InitialGrammarAction($2); }
	;

info: team formation lineup metadata							{ $$ = InfoGrammarAction($1, $2, $3, $4 ); }
	| team formation lineupNoNum metadata						{ $$ = InfoNoNumGrammarAction($1, $2, $3, $4 ); }
	| %empty													{ $$ = NULL; }
	;

team: TEAM STRING OF NUMBER PLAYERS								{ $$ = TeamNameGrammarAction($2, $4 ); }
	| TEAM OF NUMBER PLAYERS									{ $$ = TeamNoNameGrammarAction($3); }
	;

formation: FORMATION formationNumber							{ $$ = FormationGrammarAction($2); }
	;
formationNumber: FORMATIONNUMBER formationNumber				{ $$ = FormationNumberGrammarAction($1,$2); }
	| FORMATIONNUMBER											{ $$ = FormationNumberFinalGrammarAction($1); }
	;

lineup: LINEUP playerInfo substitutes							{ $$ = LineupGrammarAction($2, $3); }
	;

lineupNoNum: LINEUPNONUM playerInfoNoNum substitutesNoNum 		{ $$ = LineupNoNumGrammarAction($2, $3);}
	;	

playerInfo: NUMBER COLON STRING playerInfo						{ $$ = PlayerInfoGrammarAction($1, $3, $4); }
	| NUMBER COLON STRING										{ $$ = PlayerInfoFinalGrammarAction($1, $3); }
	;

playerInfoNoNum: STRING playerInfoNoNum							{ $$ = PlayerInfoNoNumGrammarAction($1, $2); }
	| STRING													{ $$ = PlayerInfoNoNumFinalGrammarAction($1); }
	;

substitutes: SUBSTITUTES subInfo								{ $$ = SubstitutesGrammarAction($2); }
	| %empty													{ $$ = NULL; }
	;

substitutesNoNum: SUBSTITUTESNONUM subInfoNoNum					{ $$ = SubstitutesNoNumGrammarAction($2); }
	| %empty													{ $$ = NULL; }
	;

subInfo: NUMBER COLON STRING subInfo							{$$ = SubInfoGrammarAction($1, $3, $4);}
	| NUMBER COLON STRING										{$$ = SubInfoFinalGrammarAction($1, $3);}
	;

subInfoNoNum: STRING subInfoNoNum								{$$ = SubInfoNoNumGrammarAction($1, $2);}
	| STRING													{ $$ = SubInfoNoNumFinalGrammarAction($1)}
	;

metadata: METADATA matchDate matchResult						{ $$ = MetadataCompleteGrammarAction($2, $3); }
	| 	METADATA matchResult								    { $$ = MetadataResultGrammarAction($2); }
	|	METADATA matchDate										{ $$ = MetadataDateGrammarAction($2); }
	|   %empty												    { $$ = NULL; }
	;

matchDate: DATE COLON DATESTRING								{ $$ = MatchDateGrammarAction($3); }
	;

matchResult: RESULT COLON APOSTROPHE RESULTSTRING APOSTROPHE	{ $$ = MatchResultGrammarAction($4); }
	;

%%
