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

token StartAction(const char * match){
	return START;
}

token EndAction(const char * match){
	return END;
};           
token FormationAction(const char * match){
	return FORMATION;
}; 
token FormationNumberAction(const char * match){
	yylval.string = match;
	return FORMATIONNUMBER;
};
token LineupAction(const char * match,int option){
	if (option == 0)
		return LINEUP;
	return LINEUPNONUM;
}; 
token MetadataAction(const char * match){
	return METADATA;
}; 
token DateAction(const char * match){
	return DATE;
}; 
token DateStringAction(const char * match){
	yylval.string = match;
	return DATESTRING;
}
token ResultAction(const char * match){
	return RESULT;
}; 
token ResultStringAction(const char * match){
	yylval.string = match;
	return RESULTSTRING;
}
token TeamAction(const char * match){
	return TEAM;
}; 
token OfAction(const char * match){
	return OF;
}; 
token PlayersFormationAction(const char * match){
	return PLAYERSFORMATION;
}; 
token SubsitutesAction(const char * match,int option){
	if (option == 0)
		return SUBSTITUTES;
	return SUBSTITUESNONUM;
}; 
token DashAction(const char * match){
	return DASH;
}; 
token ColonAction(const char * match){
	return COLON;
}; 
token ApostropheAction(const char * match){
	return APOSTROPHE;
}; 
token StringAction(const char * match){
	yylval.string = match;
	return STRING;
};
token NumberAction(const char * match){
	yylval=atoi(match);
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
