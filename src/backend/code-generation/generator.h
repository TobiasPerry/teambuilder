#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER

#include "../../backend/semantic-analysis/abstract-syntax-tree.h"
#include "../support/logger.h"
#include "generator.h"
#include "../support/clist.h"
#include "../semantic-analysis/symbol-table.h"
#define BUFFER_LENGTH 5000

void Generator(InitialNode * initial);
char * getPlayersArray();
char * getMatchResult(InitialNode * initial);
char * getMatchDate(InitialNode * initial);
char * getTeamName(InitialNode * initial);
char * getSubstitutesArray();
char * getFormationsArray();

#endif
