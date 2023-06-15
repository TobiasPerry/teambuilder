#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include <stdio.h>

#include "../support/clist.h"

// lista de jugadores
//lista de subs
//lista de formaciones
// resultado
// fecha
// team name
// cantidad de jugadores

typedef struct symbol_t{
    char teamName[50];
    char result[10];
    char date[11];
    int playerAmount;
    //listas
    CList  * players;
    CList  * subs;
    CList  * formations;
}symbol_t;

typedef struct player_t{
    char name[50];
    int number;
}player_t;


void symbolTableInit();

void addPlayer(char * playerName, int playerNumber);

void addSub(char * subName, int subNumber);

void addFormation(char * formationName);

void setName(char * name);

void setDate(char * date);

void setResult(char * result);


void symbolTableFree();


#endif