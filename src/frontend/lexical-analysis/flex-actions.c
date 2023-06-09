#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>

/**
 * Implementación de "flex-actions.h".
 *
 * Cada función debe realizar 2 operaciones básicas para lograr el streaming
 * de tokens hacia Bison:
 *
 *	1) Computar los atributos del token y almacenarlos donde sea conveniente
 *		(en la tabla de símbolos, en "yylval", o en ambos).
 *	2) Retornar el token que identifica el terminal identificado.
 *
 * Bison utilizará el token retornado en el punto (2) para matchear dicho
 * terminal en la gramática. Por otro lado, el valor almacenado en "yylval" es
 * el que Bison proveerá como valor semántico al realizar una reducción
 * (mediante $1, $2, $3, etc.).
 */

void BeginCommentPatternAction() {
	LogDebug("BeginCommentPatternAction.");
}

void EndCommentPatternAction() {
	LogDebug("EndCommentPatternAction.");
}

void BeginStringPatternAction(){
	LogDebug("BeginStringPatternAction.");
}

void EndStringPatternAction(){
	LogDebug("EndStringPatternAction.");
}

token StartAction(const char * match){
	yylval.token=START;
	return START;
}

token EndAction(const char * match){
	yylval.token = END;
	return END;
};           
token FormationAction(const char * match){
	yylval.token = FORMATION;
	return FORMATION;
}; 
token FormationNumberAction(const char * match, int length){
	char * number= calloc(length+1, sizeof(char));
	strncpy(number, match, length);
	number[length] = '\0';

	yylval.string = (char*) number;
	return FORMATIONNUMBER;
};
token LineupAction(const char * match,int option){
	if (option == 0){
		yylval.token = LINEUP;
		return LINEUP;
	}
	yylval.token = LINEUPNONUM;
	return LINEUPNONUM;
}; 
token MetadataAction(const char * match){
	yylval.token = METADATA;
	return METADATA;
}; 
token DateAction(const char * match){
	yylval.token = DATE;
	return DATE;
}; 
token DateStringAction(const char * match, int length){
	char * date= calloc(length+1, sizeof(char));
	strncpy(date, match, length);
	date[length] = '\0';
	
	yylval.string = date;
	return DATESTRING;
}
token ResultAction(const char * match){
	yylval.token = RESULT;
	return RESULT;
}; 
token ResultStringAction(const char * match, int length){
	char * result= calloc(length+1, sizeof(char));
	strncpy(result, match, length);
	result[length] = '\0';

	yylval.string = result;
	return RESULTSTRING;
}
token TeamAction(const char * match){
	yylval.token = TEAM;
	return TEAM;
}; 
token OfAction(const char * match){
	yylval.token = OF;
	return OF;
}; 
token PlayersAction(const char * match){
	yylval.token = PLAYERS;
	return PLAYERS;
}; 
token SubstitutesAction(const char * match,int option){
	if (option == 0){
		yylval.token = SUBSTITUTES;
		return SUBSTITUTES;
	}
	yylval.token = SUBSTITUTESNONUM;
	return SUBSTITUTESNONUM;
}; 


token ColonAction(const char * match){
	yylval.token = COLON;
	return COLON;
}; 
token ApostropheAction(const char * match){
	yylval.token = APOSTROPHE;
	return APOSTROPHE;
}; 
token StringAction(const char * match, int length){
	char * string= calloc(length+1, sizeof(char));
	strncpy(string, match, length);
	string[length] = '\0';

	yylval.string = string;
	return STRING;
};

token NumberAction(const char * match, int length){
	char * number= calloc(length+1, sizeof(char));
	strncpy(number, match, length);
	
	number[length] = '\0';

	yylval.integer=atoi(number);
	free(number);
	return NUMBER;
};
token UnknownPatternAction(const char * lexeme, const int length) {
	LogDebug("UnknownPatternAction: '%s' (length = %d).", lexeme, length);
	yylval.token = YYUNDEF;
	// Al emitir este token, el compilador aborta la ejecución.
	return YYUNDEF;
}
void IgnoredPatternAction(const char * lexeme, const int length) {
	LogDebug("IgnoredPatternAction: '%s' (length = %d).", lexeme, length);
	// Como no debe hacer nada con el patrón, solo se loguea en consola.
}
