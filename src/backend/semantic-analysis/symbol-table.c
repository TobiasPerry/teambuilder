#include "symbol-table.h"


symbol_t *symbolTable = NULL;


void symbolTableInit(){
    if(symbolTable != NULL){
        printf("Symbol table already initialized\n");
        return;
    }

    symbolTable = malloc(sizeof(symbol_t));

    symbolTable->players = CList_init(sizeof(player_t));
    symbolTable->subs = CList_init(sizeof(player_t));
    symbolTable->formations = CList_init(sizeof(char[10]));
}

void addPlayer(char * playerName, int playerNumber){
    player_t player;
    strcpy(player.name, playerName);
    player.number = playerNumber;
    symbolTable->players->add(symbolTable->players, &player);
}

void addSub(char * subName, int subNumber){
    player_t sub;
    strcpy(sub.name, subName);
    sub.number = subNumber;
    symbolTable->subs->add(symbolTable->subs, &sub);
}

void addFormation(char * formationName){
    symbolTable->formations->add(symbolTable->formations, formationName);
}


void symbolTableFree(){
    if(symbolTable == NULL){
        printf("Symbol table already freed\n");
        return;
    }

    symbolTable->players->free(symbolTable->players);
    symbolTable->subs->free(symbolTable->subs);
    symbolTable->formations->free(symbolTable->formations);
    free(symbolTable);
    symbolTable = NULL;
}


