#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

//#include "listADT.h"

// lista de jugadores
//lista de subs
//lista de formaciones
// resultado
// fecha
// team name
// cantidad de jugadores

typedef struct {
    char teamName[50];
    char result[10];
    char date[11];
    int playerAmount;
    //listas
    listADT players;
    listADT subs;
    listADT formations;
}symbol_t;

#endif