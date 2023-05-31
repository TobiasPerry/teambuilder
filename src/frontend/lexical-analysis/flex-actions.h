#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../syntactic-analysis/bison-parser.h"

/**
 * Se definen las acciones a ejecutar sobre cada patrón hallado mediante el
 * analizador léxico Flex. Este analizador solo puede identificar
 * construcciones regulares, ya que utiliza un autómata finito determinístico
 * (a.k.a. DFA), como mecanismo de escaneo y reconocimiento.
 *
 * Debería existir una acción por cada patrón disponible en Flex (es decir,
 * por cada regla).
 *
 * Solo aquellas acciones que tengan interés en conocer el largo del lexema
 * emplean el parámetro adicional "length". Esto es útil cuando se desea
 * asignar memoria dinámica, y por lo tanto, se debe saber exactamente el
 * largo de aquello que se va a almacenar.
 */

// Bloque de comentarios multilínea.
void BeginCommentPatternAction();
void EndCommentPatternAction();


//Strings
void BeginStringPatternAction();
void EndStringPatternAction();
token StringAction(const char * match);


// Patrones terminales del lenguaje diseñado.
token StartAction(const char * match); 
token EndAction(const char * match);           
token FormationAction(const char * match); 
token FormationNumberAction(const char * match);
token LineupAction(const char * match,int option); 
token LineupAction(const char * match,int option); 
token MetadataAction(const char * match); 
token DateAction(const char * match); 
token ResultAction(const char * match); 
token TeamAction(const char * match); 
token OfAction(const char * match); 
token PlayersAction(const char * match); 
token SubstitutesAction(const char * match,int option); 
token ColonAction(const char * match); 
token ApostropheAction(const char * match); 
token NumberAction(const char * match);
token DateStringAction(const char * match);
token ResultStringAction(const char * match);

// Patrón desconocido, permite abortar debido a un error de sintaxis.
token UnknownPatternAction(const char * lexeme, const int length);

// Regla que no hace nada, permite ignorar parte de la entrada.
void IgnoredPatternAction(const char * lexeme, const int length);

#endif
