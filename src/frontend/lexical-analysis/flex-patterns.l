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
whitespaceOrEndline		[ \f\n\r\t\v]
endline			        [\n]
string                  '[\-A-Za-z ]+'

%%

"/*"										                { BEGIN(COMMENT); BeginCommentPatternAction(); }
<COMMENT>.									                { ; }
<COMMENT>{endline}							                { ; }
<COMMENT>"*/"								                { EndCommentPatternAction(); BEGIN(INITIAL); }

"START"                                                     { return StartAction(yytext); }
"END"                                                       { return EndAction(yytext); }           
"FORMATION"                                                 { return FormationAction(yytext); }
"TEAM"                                                      { return TeamAction(yytext); }
"OF"                                                        { return OfAction(yytext); }
"PLAYERS"                                                   { return PlayersAction(yytext); }
"SUBSTITUTES"                                               { return SubstitutesAction(yytext, HASNUM); }
"SUBSTITUTESNONUM"                                          { return SubstitutesAction(yytext, HASNONUM); }
"LINEUPNONUM"                                               { return LineupAction(yytext,HASNONUM); }
"LINEUP"                                                    { return LineupAction(yytext,HASNUM); }
"METADATA"                                                  { return MetadataAction(yytext); }
"DATE"                                                      { return DateAction(yytext); }
"RESULT"                                                    { return ResultAction(yytext); }
[0-9]-[0-9]-[0-9]                                           { return FormationNumberAction(yytext, yyleng);}
'[0-9]{4}-(0[1-9]|[1-2][0-9]|3[0-1])-(0[1-9]|1[0-2])'       { return DateStringAction(yytext, yyleng);}
[0-9]+-[0-9]+                                               { return ResultStringAction(yytext, yyleng);}
":"                                                         { return ColonAction(yytext); }
"'"                                                         { return ApostropheAction(yytext); }
{string}                                                    { return StringAction(yytext, yyleng);}
{number}                                                    { return NumberAction(yytext, yyleng);}  
{whitespaceOrEndline}						                { IgnoredPatternAction(yytext, yyleng); }

.											                { return UnknownPatternAction(yytext, yyleng); }

%%   