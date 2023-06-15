#ifndef _SYMBOL_TABLE_H
#define _SYMBOL_TABLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../support/clist.h"

// lista de jugadores
//lista de subs
//lista de formaciones
// resultado
// fecha
// team name
// cantidad de jugadores

typedef struct symbol_t{
    //listas
    CList  * players;
    CList  * subs;
    CList  * formations;
}symbol_t;

typedef struct player_t{
    char name[100];
    int number;
}player_t;

//inicia la tabla de simbolos
void symbolTableInit();

void addPlayer(char * playerName, int playerNumber);

void addSub(char * subName, int subNumber);

void addFormation(char * formationName);

symbol_t * getSymbolTable();


void symbolTableFree();


#endif