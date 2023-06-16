#include "backend/code-generation/generator.h"
#include "backend/support/logger.h"
#include "backend/support/shared.h"
#include "frontend/syntactic-analysis/bison-parser.h"
#include <stdio.h>
#include "backend/semantic-analysis/symbol-table.h"

// Estado de la aplicación.
CompilerState state;

// Punto de entrada principal del compilador.
const int main(const int argumentCount, const char ** arguments) {
	// Inicializar estado de la aplicación.
	state.program = NULL;
	state.result = 0;
	state.succeed = false;
	;
	// Mostrar parámetros recibidos por consola.
	for (int i = 0; i < argumentCount; ++i) {
		LogInfo("Argumento %d: '%s'", i, arguments[i]);
	}
	symbolTableInit();
	

	// Compilar el programa de entrada.
	LogInfo("Compilando...\n");
	const int result = yyparse();
	switch (result) {
		case 0:
			// La variable "succeed" es la que setea Bison al identificar el símbolo
			// inicial de la gramática satisfactoriamente.
			if (state.succeed) {
				LogInfo("La compilacion fue exitosa.");
				Generator(state.program);
			}
			else {
				LogError("Se produjo un error en la aplicacion.");
				return -1;
			}
			break;
		case 1:
			LogError("Bison finalizo debido a un error de sintaxis.");
			break;
		case 2:
			LogError("Bison finalizo abruptamente debido a que ya no hay memoria disponible.");
			break;
		default:
			LogError("Error desconocido mientras se ejecutaba el analizador Bison (codigo %d).", result);
	}
	symbol_t * symbol = getSymbolTable();
	player_t * player = symbol->players->at(symbol->players, 0);
	player_t * sub = symbol->subs->at(symbol->subs, 0);
	for(int i=0; i < symbol->formations->count(symbol->formations); i++){
		char * formation = symbol->formations->at(symbol->formations, i);
		printf(" formation : %s\n", formation);
	}
	for(int i =0; i < symbol->subs->count(symbol->subs); i++){
		player_t * sub = symbol->subs->at(symbol->subs, i);
		printf("%s %d\n", sub->name, sub->number);
	}
	

	//LogInfo("%s", player->name );
	
	symbolTableFree();

	LogInfo("Fin.");
	return result;
}
