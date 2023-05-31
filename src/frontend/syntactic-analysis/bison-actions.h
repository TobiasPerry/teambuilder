#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

// Programa.
InitialNode * InitialGrammarAction(InfoNode * info);
InfoNode * InfoGrammarAction(TeamNode * team, FormationNode * formation, LineupNode * lineup, MetadataNode * metadata);
InfoNoNumNode * InfoNoNumGrammarAction(TeamNode * team, FormationNode * formation, LineupNoNumNode * lineupNoNum, MetadataNode * metadata);
TeamNode * TeamNameGrammarAction(char * teamName, int players);
TeamNode * TeamNoNameGrammarAction(int players);
FormationNode * FormationGrammarAction(FormationNumberNode * formationNumber);
FormationNumberNode * FormationNumberGrammarAction(char * formationNumber, FormationNumberNode * nextFormationNumber);
FormationNumberNode * FormationNumberFinalGrammarAction(char * formationNumber);
LineupNode * LineupGrammarAction( PlayerInfoNode * playerInfo,SubstitutesNode * substitutes);
LineupNoNumNode * LineupNoNumGrammarAction( PlayerInfoNoNumNode * playerInfoNoNum,SubstitutesNoNumNode * substitutesNoNum);
PlayerInfoNode * PlayerInfoGrammarAction(int number, char * name, PlayerInfoNode * nextPlayerInfo);
PlayerInfoNode * PlayerInfoFinalGrammarAction(int number, char * name);
PlayerInfoNoNumNode * PlayerInfoNoNumGrammarAction(char * name, PlayerInfoNoNumNode * nextPlayerInfoNoNum);
PlayerInfoNoNumNode * PlayerInfoNoNumFinalGrammarAction(char * name);
SubstitutesNode * SubstitutesGrammarAction(PlayerInfoNode * playerInfo);
SubstitutesNoNumNode * SubstitutesNoNumGrammarAction(PlayerInfoNoNumNode * playerInfoNoNum);
MetadataNode * MetadataCompleteGrammarAction(MatchDateNode * matchDate, MatchResultNode * matchResult);
MetadataNode * MetadataDateGrammarAction(MatchDateNode * matchDate);
MetadataNode * MetadataResultGrammarAction(MatchResultNode * matchResult);
MatchDateNode * MatchDateGrammarAction(char * date);
MatchResultNode * MatchResultGrammarAction(char * result);





int Return0();



#endif
