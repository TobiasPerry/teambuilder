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
whitespaceOrEndline		[\f\n\r\t\v]
endline			        [\n]
string                  '[\-A-Za-z ]+'
white                   [ ]

%%

"/*"										                { BEGIN(COMMENT); BeginCommentPatternAction(); }
<COMMENT>.									                { ; }
<COMMENT>{endline}							                { ; }
<COMMENT>"*/"								                { EndCommentPatternAction(); BEGIN(INITIAL); }

{white}                                                     { IgnoredPatternAction(yytext, yyleng); }
"START"                                                     { return StartAction(yytext); }
"END"                                                       { return EndAction(yytext); }           
"FORMATION"                                                 { return FormationAction(yytext); }
"TEAM"                                                      { return TeamAction(yytext); }
"OF"                                                        { return OfAction(yytext); }
"PLAYERS"                                                   { return PlayersAction(yytext); }
"SUBSTITUTES"                                               { return SubstitutesAction(yytext, NUM); }
"SUBSTITUTESNONUM"                                          { return SubstitutesAction(yytext, NONUM); }
"LINEUPNONUM"                                               { return LineupAction(yytext,NONUM); }
"LINEUP"                                                    { return LineupAction(yytext,NUM); }
"METADATA"                                                  { return MetadataAction(yytext); }
"DATE"                                                      { return DateAction(yytext); }
"RESULT"                                                    { return ResultAction(yytext); }
[0-9]-[0-9]-[0-9]                                           { return FormationNumberAction(yytext);}
'[0-9]{4}-(0[1-9]|[1-2][0-9]|3[0-1])-(0[1-9]|1[0-2])'       { return DateStringAction(yytext);}
[0-9]+-[0-9]+                                               { return ResultStringAction(yytext);}
":"                                                         { return ColonAction(yytext); }
"'"                                                         { return ApostropheAction(yytext); }
{string}                                                    { return StringAction(yytext);}
{number}                                                    { return NumberAction(yytext);}   
{whitespaceOrEndline}						                { IgnoredPatternAction(yytext, yyleng); }


.											                { return UnknownPatternAction(yytext, yyleng); }

%%   