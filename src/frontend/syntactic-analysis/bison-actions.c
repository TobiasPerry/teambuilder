#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"


/**
 * Implementación de "bison-grammar.h".
 */

/**
* Esta función se ejecuta cada vez que se emite un error de sintaxis.
*/
void yyerror(const char * string) {
	LogError("Mensaje: '%s' debido a '%s' (linea %d).", string, yytext, yylineno);
	LogError("En ASCII es:");
	LogErrorRaw("\t");
	const int length = strlen(yytext);
	for (int i = 0; i < length; ++i) {
		LogErrorRaw("[%d]", yytext[i]);
	}
	LogErrorRaw("\n\n");
}

/**
* Esta acción se corresponde con el no-terminal que representa el símbolo
* inicial de la gramática, y por ende, es el último en ser ejecutado, lo que
* indica que efectivamente el programa de entrada se pudo generar con esta
* gramática, o lo que es lo mismo, que el programa pertenece al lenguaje.
*/
// int InitialAction(const int value) {
// 	LogDebug("\tProgramGrammarAction(%d)", value);
// 	/*
// 	* "state" es una variable global que almacena el estado del compilador,
// 	* cuyo campo "succeed" indica si la compilación fue o no exitosa, la cual
// 	* es utilizada en la función "main".
// 	*/
// 	state.succeed = true;
// 	/*
// 	* Por otro lado, "result" contiene el resultado de aplicar el análisis
// 	* sintáctico mediante Bison, y almacenar el nood raíz del AST construido
// 	* en esta variable. Para el ejemplo de la calculadora, no hay AST porque
// 	* la expresión se computa on-the-fly, y es la razón por la cual esta
// 	* variable es un simple entero, en lugar de un nodo.
// 	*/
// 	state.result = value;
// 	return value;
// }

InitialNode * InitialGrammarAction(InfoNode * info){
	InitialNode * initial = (InitialNode *) calloc(1, sizeof(InitialNode));
	initial->info = info;
	state.succeed = true;
	state.result = 15;
	state.program = initial;
	return initial;
}

int Return0(){
	return 0;
}

InfoNode * InfoGrammarAction(TeamNode * team, FormationNode * formation, LineupNode * lineup, MetadataNode * metadata){
	InfoNode * info = (InfoNode *) calloc(1, sizeof(InfoNode));
	info->team = team;
	info->formation = formation;
	info->lineup = lineup;
	info->metadata = metadata;
	info->numeration = NUM;
	return info;
}

InfoNoNumNode * InfoNoNumGrammarAction(TeamNode * team, FormationNode * formation, LineupNoNumNode * lineupNoNum, MetadataNode * metadata){
	InfoNoNumNode * info = (InfoNoNumNode *) calloc(1, sizeof(InfoNoNumNode));
	info->team = team;
	info->formation = formation;
	info->lineupNoNum = lineupNoNum;
	info->metadata = metadata;
	info->numeration = NONUM;
	return info;
}

TeamNode * TeamNameGrammarAction(char * name, int players){
	TeamNode * team = (TeamNode *) calloc(1, sizeof(TeamNode));
	team->teamName = name;
	team->teamNumber = players;
	team->teamType = TEAMNAME;
	return team;
}

TeamNode * TeamNoNameGrammarAction(int players){
	TeamNode * team = (TeamNode *) calloc(1, sizeof(TeamNode));
	team->teamNumber = players;
	team->teamType = NOTEAMNAME;
	return team;
}

FormationNode * FormationGrammarAction(FormationNumberNode * formationNumber){
	FormationNode * formation = (FormationNode *) calloc(1, sizeof(FormationNode));
	formation->formationNumber = formationNumber;
	return formation;
}

FormationNumberNode * FormationNumberGrammarAction(char * formationNumber, FormationNumberNode * nextFormationNumber){
	FormationNumberNode * formationNumber2 = (FormationNumberNode *) calloc(1, sizeof(FormationNumberNode));
	formationNumber2->formationNumber = formationNumber;
	formationNumber2->nextFormationNumber = nextFormationNumber;
	formationNumber2->formationNumberType = NOFINAL;
	addFormation(formationNumber);

	//le agregue un 2 porque me parecio que habia un error aca
	return formationNumber2;
}

FormationNumberNode * FormationNumberFinalGrammarAction(char * formationNumber){
	FormationNumberNode * formationNumber2 = (FormationNumberNode *) calloc(1, sizeof(FormationNumberNode));
	formationNumber2->formationNumber = formationNumber;
	formationNumber2->formationNumberType = FINAL;
	addFormation(formationNumber);
	return formationNumber2;
}

LineupNode * LineupGrammarAction(PlayerInfoNode * playerInfo, SubstitutesNode * substitutes){
	LineupNode * lineup = (LineupNode *) calloc(1, sizeof(LineupNode));
	lineup->playerInfo = playerInfo;
	lineup->substitutes = substitutes;
	return lineup;
}

LineupNoNumNode * LineupNoNumGrammarAction(PlayerInfoNoNumNode * playerInfoNoNum, SubstitutesNoNumNode * substitutesNoNum){
	LineupNoNumNode * lineupNoNum = (LineupNoNumNode *) calloc(1, sizeof(LineupNoNumNode));
	lineupNoNum->playerInfoNoNum = playerInfoNoNum;
	lineupNoNum->substitutesNoNum = substitutesNoNum;
	return lineupNoNum;
}

PlayerInfoNode * PlayerInfoGrammarAction(int number, char * name, PlayerInfoNode * nextPlayerInfo){
	PlayerInfoNode * playerInfo = (PlayerInfoNode *) calloc(1, sizeof(PlayerInfoNode));
	playerInfo->playerNumber = number;
	playerInfo->playerName = name;
	playerInfo->nextPlayerInfo = nextPlayerInfo;
	addPlayer(name, number);
	return playerInfo;
}

PlayerInfoNode * PlayerInfoFinalGrammarAction(int number, char * name){
	PlayerInfoNode * playerInfo = (PlayerInfoNode *) calloc(1, sizeof(PlayerInfoNode));
	playerInfo->playerNumber = number;
	playerInfo->playerName = name;
	addPlayer(name,number);
	return playerInfo;
}

PlayerInfoNoNumNode * PlayerInfoNoNumGrammarAction(char * name, PlayerInfoNoNumNode * nextPlayerInfoNoNum){
	PlayerInfoNoNumNode * playerInfoNoNum = (PlayerInfoNoNumNode *) calloc(1, sizeof(PlayerInfoNoNumNode));
	playerInfoNoNum->playerName = name;
	playerInfoNoNum->nextPlayerInfoNoNum = nextPlayerInfoNoNum;
	addPlayer(name, -1);

	return playerInfoNoNum;
}

PlayerInfoNoNumNode * PlayerInfoNoNumFinalGrammarAction(char * name){
	PlayerInfoNoNumNode * playerInfoNoNum = (PlayerInfoNoNumNode *) calloc(1, sizeof(PlayerInfoNoNumNode));
	playerInfoNoNum->playerName = name;
	addPlayer(name, -1);
	return playerInfoNoNum;
}


SubInfoNode * SubInfoGrammarAction(int number, char * subName, SubInfoNode * nextSub){
	SubInfoNode * subInfo = (SubInfoNode *)calloc(1, sizeof(SubInfoNode));
	subInfo->substituteName = subName;
	subInfo->substituteNumber = number;
	subInfo->nextSubstitute = nextSub;
	addSub(subName, number);
	return subInfo;
}


SubInfoNoNumNode * SubInfoNoNumGrammarAction( char * subName, SubInfoNoNumNode * nextSub){
	SubInfoNoNumNode * subInfoNoNum = (SubInfoNoNumNode *)calloc(1, sizeof(SubInfoNoNumNode));
	subInfoNoNum->substituteName = subName;
	subInfoNoNum->nextSubstitute = nextSub;
	addSub(subName, -1);
	return subInfoNoNum;
}


SubInfoNode * SubInfoFinalGrammarAction( int number, char * subName){
	SubInfoNode * subInfo = (SubInfoNode *)calloc(1, sizeof(SubInfoNode));
	subInfo->substituteName = subName;
	subInfo->substituteNumber = number;
	subInfo->nextSubstitute = NULL;
	addSub(subName, number);
	return subInfo;
}


SubInfoNoNumNode * SubInfoNoNumFinalGrammarAction(char * subName){
	SubInfoNoNumNode * subInfoNoNum = (SubInfoNoNumNode *)calloc(1, sizeof(SubInfoNoNumNode));
	subInfoNoNum->substituteName = subName;
	subInfoNoNum->nextSubstitute = NULL;
	addSub(subName, -1);
	return subInfoNoNum;
}


SubstitutesNode * SubstitutesGrammarAction(SubInfoNode * subInfo){
	SubstitutesNode * substitutes = (SubstitutesNode *) calloc(1, sizeof(SubstitutesNode));
	substitutes->substituteName = subInfo->substituteName;
	substitutes->substituteNumber = subInfo->substituteNumber;
	substitutes->nextSubstitute = subInfo->nextSubstitute;
	return substitutes;
}

SubstitutesNoNumNode * SubstitutesNoNumGrammarAction(SubInfoNoNumNode * subInfoNoNum){
	SubstitutesNoNumNode * substitutesNoNum = (SubstitutesNoNumNode *) calloc(1, sizeof(SubstitutesNoNumNode));
	substitutesNoNum->substituteName = subInfoNoNum->substituteName;
	substitutesNoNum->nextSubstituteNoNum = subInfoNoNum->nextSubstitute;
	return substitutesNoNum;
}

MetadataNode * MetadataCompleteGrammarAction(MatchDateNode * matchDate, MatchResultNode * matchResult){
	MetadataNode * metadata = (MetadataNode *) calloc(1, sizeof(MetadataNode));
	metadata->matchDate = matchDate;
	metadata->matchResult = matchResult;
	metadata->metadataType = COMPLETE;
	return metadata;
}

MetadataNode * MetadataDateGrammarAction(MatchDateNode * matchDate){
	MetadataNode * metadata = (MetadataNode *) calloc(1, sizeof(MetadataNode));
	metadata->matchDate = matchDate;
	metadata->metadataType = HASDATE;
	return metadata;
}

MetadataNode * MetadataResultGrammarAction(MatchResultNode * matchResult){
	MetadataNode * metadata = (MetadataNode *) calloc(1, sizeof(MetadataNode));
	metadata->matchResult = matchResult;
	metadata->metadataType = HASRESULT;
	return metadata;
}

MatchDateNode * MatchDateGrammarAction(char * date){
	MatchDateNode * matchDate = (MatchDateNode *) calloc(1, sizeof(MatchDateNode));
	matchDate->date = date;
	return matchDate;
}

MatchResultNode * MatchResultGrammarAction(char * result){
	MatchResultNode * matchResult = (MatchResultNode *) calloc(1, sizeof(MatchResultNode));
	matchResult->result = result;
	return matchResult;
}

