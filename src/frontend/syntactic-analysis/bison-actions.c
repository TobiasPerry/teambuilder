#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>

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
int InitialAction(const int value) {
	LogDebug("\tProgramGrammarAction(%d)", value);
	/*
	* "state" es una variable global que almacena el estado del compilador,
	* cuyo campo "succeed" indica si la compilación fue o no exitosa, la cual
	* es utilizada en la función "main".
	*/
	state.succeed = true;
	/*
	* Por otro lado, "result" contiene el resultado de aplicar el análisis
	* sintáctico mediante Bison, y almacenar el nood raíz del AST construido
	* en esta variable. Para el ejemplo de la calculadora, no hay AST porque
	* la expresión se computa on-the-fly, y es la razón por la cual esta
	* variable es un simple entero, en lugar de un nodo.
	*/
	state.result = value;
	return value;
}

InitialNode * InitialAction(InfoNode * info){
	InitalNode * initial = (InitialNode *) calloc(1, sizeof(InitialNode));
	initial->info = info;
	return initial;
}

InfoNode * InfoAction(TeamNode * team, FormationNode * formation, LineupNode * lineup, MetadataNode * metadata){
	InfoNode * info = (InfoNode *) calloc(1, sizeof(InfoNode));
	info->team = team;
	info->formation = formation;
	info->lineup = lineup;
	info->metadata = metadata;
	info->numeration = NUM;
	return info;
}

InfoNode * InfoNoNumAction(TeamNode * team, FormationNode * formation, LineupNoNumNode * lineupNoNum, MetadataNode * metadata){
	InfoNode * info = (InfoNode *) calloc(1, sizeof(InfoNode));
	info->team = team;
	info->formation = formation;
	info->lineupNoNum = lineupNoNum;
	info->metadata = metadata;
	info->numeration = NONUM;
	return info;
}

TeamNode * TeamNameAction(char * name, int players){
	TeamNode * team = (TeamNode *) calloc(1, sizeof(TeamNode));
	team->teamName = name;
	team->teamNumber = players;
	team->teamType = TEAMNAME;
	return team;
}

TeamNode * TeamNoNameAction(int players){
	TeamNode * team = (TeamNode *) calloc(1, sizeof(TeamNode));
	team->teamNumber = players;
	team->teamType = NOTEAMNAME;
	return team;
}

FormationNode * FormationAction(FormationNumberNode * formationNumber){
	FormationNode * formation = (FormationNode *) calloc(1, sizeof(FormationNode));
	formation->formationNumber = formationNumber;
	return formation;
}

FormationNumberNode * FormationNumberAction(char * formationNumber, FormationNumberNode * nextFormationNumber){
	FormationNumberNode * formationNumber = (FormationNumberNode *) calloc(1, sizeof(FormationNumberNode));
	formationNumber->formationNumber = formationNumber;
	formationNumber->nextFormationNumber = nextFormationNumber;
	formationNumber->formationNumberType = NOFINAL;
	return formationNumber;
}

FormationNumberNode * FormationNumberFinalAction(char * formationNumber){
	FormationNumberNode * formationNumber = (FormationNumberNode *) calloc(1, sizeof(FormationNumberNode));
	formationNumber->formationNumber = formationNumber;
	formationNumber->formationNumberType = FINAL;
	return formationNumber;
}

LineupNode * LineupAction(PlayerInfoNode * playerInfo, SubstitutesNode * substitutes){
	LineupNode * lineup = (LineupNode *) calloc(1, sizeof(LineupNode));
	lineup->playerInfo = playerInfo;
	lineup->substitutes = substitutes;
	return lineup;
}

LineupNoNumNode * LineupNoNumAction(PlayerInfoNoNumNode * playerInfoNoNum, SubstitutesNoNumNode * substitutesNoNum){
	LineupNoNumNode * lineupNoNum = (LineupNoNumNode *) calloc(1, sizeof(LineupNoNumNode));
	lineupNoNum->playerInfoNoNum = playerInfoNoNum;
	lineupNoNum->substitutesNoNum = substitutesNoNum;
	return lineupNoNum;
}

PlayerInfoNode * PlayerInfoAction(int number, char * name, PlayerInfoNode * nextPlayerInfo){
	PlayerInfoNode * playerInfo = (PlayerInfoNode *) calloc(1, sizeof(PlayerInfoNode));
	playerInfo->playerNumber = number;
	playerInfo->playerName = name;
	playerInfo->nextPlayerInfo = nextPlayerInfo;
	return playerInfo;
}


int Return0(){
	return 0;
}





// int AdditionExpressionGrammarAction(const int leftValue, const int rightValue) {
// 	LogDebug("\tAdditionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
// 	return Add(leftValue, rightValue);
// }

// int SubtractionExpressionGrammarAction(const int leftValue, const int rightValue) {
// 	LogDebug("\tSubtractionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
// 	return Subtract(leftValue, rightValue);
// }

// int MultiplicationExpressionGrammarAction(const int leftValue, const int rightValue) {
// 	LogDebug("\tMultiplicationExpressionGrammarAction(%d, %d)", leftValue, rightValue);
// 	return Multiply(leftValue, rightValue);
// }

// int DivisionExpressionGrammarAction(const int leftValue, const int rightValue) {
// 	LogDebug("\tDivisionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
// 	return Divide(leftValue, rightValue);
// }

// int FactorExpressionGrammarAction(const int value) {
// 	LogDebug("\tFactorExpressionGrammarAction(%d)", value);
// 	return value;
// }

// int ExpressionFactorGrammarAction(const int value) {
// 	LogDebug("\tExpressionFactorGrammarAction(%d)", value);
// 	return value;
// }

// int ConstantFactorGrammarAction(const int value) {
// 	LogDebug("\tConstantFactorGrammarAction(%d)", value);
// 	return value;
// }

// int IntegerConstantGrammarAction(const int value) {
// 	LogDebug("\tIntegerConstantGrammarAction(%d)", value);
// 	return value;
//}
