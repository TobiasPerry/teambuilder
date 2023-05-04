%{

#include "flex-actions.h"

%}

/* Obliga a crear una regla explícita para manejar lexemas desconocidos. */
%option nodefault

/* Escanea un único archivo y se detiene. */
%option noyywrap

/* Dispone una variable global "yylineno" con el número de línea actual. */
%option yylineno

/* Contextos de Flex. */
%x COMMENT

/* Patrones reutilizables. */
number			        [1-9][0-9]*
whitespaceOrEndline		[ \f\n\r\t\v\n]
string                  [A-Za-z ]+

%%

"/*"										                { BEGIN(COMMENT); BeginCommentPatternAction(); }
<COMMENT>.									                { ; }
<COMMENT>{whitespaceOrEndline}							                { ; }
<COMMENT>"*/"								                { EndCommentPatternAction(); BEGIN(INITIAL); }


"START"                                                     { return StartAction(yytext); }
"END"                                                       { return EndAction(yytext); }           
"FORMATION"                                                 { return FormationAction(yytext); }
[0-9]-[0-9]-[0-9]                                           { return FormationNumberAction(yytext);}
"LINEUPNONUM"                                               { return LineupAction(yytext,1); }
"LINEUP"                                                    { return LineupAction(yytext,0); }
"METADATA"                                                  { return MetadataAction(yytext); }
"DATE"                                                      { return DateAction(yytext); }
(0[1-9]|[1-2][0-9]|3[0-1])-(0[1-9]|1[0-2])-[0-9]{4}         { return DateStringAction(yytext);}
"RESULT"                                                    { return ResultAction(yytext); }
[0-9]+-[0-9]+                                               { return ResultStringAction(yytext);}
"TEAM"                                                      { return TeamAction(yytext); }
"OF"                                                        { return OfAction(yytext); }
"PLAYERSFORMATION"                                          { return PlayersFormationAction(yytext); }
"SUBSTITUTES"                                                { return SubstitutesAction(yytext, 0); }
"SUBSTITUTESNONUM"                                           { return SubstitutesAction(yytext, 1); }
"-"                                                         { return DashAction(yytext); }
":"                                                         { return ColonAction(yytext); }
"'"                                                         { return ApostropheAction(yytext); }
{string}                                                    { return StringAction(yytext);}
{number}                                                    { return NumberAction(yytext);}   

{whitespaceOrEndline}						                { IgnoredPatternAction(yytext, yyleng); }

.											                { return UnknownPatternAction(yytext, yyleng); }

%%
