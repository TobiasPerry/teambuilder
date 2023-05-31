#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"

/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

// Programa.
InitialNode * InitialAction(InfoNode * info);
InfoNode * InfoAction(TeamNode * team, FormationNode * formation, LineupNode * lineup, MetadataNode * metadata);
InfoNode * InfoNoNumAction(TeamNode * team, FormationNode * formation, LineupNoNumNode * lineupNoNum, MetadataNode * metadata)
TeamNode * TeamNameAction(char * teamName, int players);
TeamNode * TeamNoNameAction(int players);
FormationNode * FormationAction(FormationNumberNode * formationNumber);
FormationNumberNode * FormationNumberAction(char * formationNumber, FormationNumberNode * nextFormationNumber);
FormationNumberNode * FormationNumberFinalAction(char * formationNumber);
LineupNode * LineupAction( PlayerInfoNode * playerInfo,SubstitutesNode * substitutes);
LineupNoNumNode * LineupNoNumAction( PlayerInfoNoNumNode * playerInfoNoNum,SubstitutesNoNumNode * substitutesNoNum);
PlayerInfoNode * PlayerInfoAction(int number, char * name, PlayerInfoNode * nextPlayerInfo);
PlayerInfoNode * PlayerInfoFinalAction(int number, char * name);
PlayerInfoNoNumNode * PlayerInfoNoNumAction(char * name, PlayerInfoNoNumNode * nextPlayerInfoNoNum);
PlayerInfoNoNumNode * PlayerInfoNoNumFinalAction(char * name);
SubstitutesNode * SubstitutesAction(PlayerInfoNode * playerInfo);
SubstitutesNoNumNode * SubstitutesNoNumAction(PlayerInfoNoNumNode * playerInfoNoNum);
MetadataNode * MetadataCompleteAction(MatchDateNode * matchDate, MatchResultNode * matchResult);
MetadataNode * MetadataDateAction(MatchDateNode * matchDate);
MetadataNode * MetadataResultAction(MatchResultNode * matchResult);
MatchDateNode * MatchDateAction(char * date);
MatchResultNode * MatchResultAction(char * result);





int Return0();

// // Expresión.
// int AdditionExpressionGrammarAction(const int leftValue, const int rightValue);
// int SubtractionExpressionGrammarAction(const int leftValue, const int rightValue);
// int MultiplicationExpressionGrammarAction(const int leftValue, const int rightValue);
// int DivisionExpressionGrammarAction(const int leftValue, const int rightValue);
// int FactorExpressionGrammarAction(const int value);

// // Factores.
// int ExpressionFactorGrammarAction(const int value);
// int ConstantFactorGrammarAction(const int value);

// // Constantes.
// int IntegerConstantGrammarAction(const int value);

#endif
