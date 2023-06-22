# Teambuilder

Un compilador para crear formaciones de equipos de futbol. 

Basado en el compilador "Flex-Bison-Compiler" de Agustin Golmar:
https://github.com/agustin-golmar/Flex-Bison-Compiler

## Grupo
* Manuel Esteban Dithurbide (62057)
* Martin Hecht (62041)
* Tomas Camilo Gay Bare (62103)
* Tobias Perry (62064)

## Sintaxis

* START
* TEAM 'teamName'[opcional] OF playerAmount PLAYERS
* FORMATION
* formation [pueden ser mas de una]
* Tag LINEUP/LINEUPNONUM
* number: 'player name' [en caso de LINEUPNONUM solo se requiere nombre del jugador] {lista}
* SUBSTITUTES/SUBSITUTESNONUM [debe coincidir con el tipo de LINEUP] [opcional]
* number: 'player name' {lista}
* METADATA [opcional]
* DATE: 'fecha' [opcional] RESULT 'result' [opcional]
* END

Obs: los whitespaces son ignorados

Algunos casos de uso (puede encontrar mas en la carpeta de tests): 

```
START
TEAM 'The Red Devils' OF 5 PLAYERS
FORMATION
2-1-1
LINEUP
1: 'El Manco'
2: 'Alves Daniel'
3: 'Pedrito Lopez'
4: 'Gaston Perez'
5: 'Pepito Radiactivo'
SUBSTITUTES
6: 'La Maquina'
7: 'Pedrito'
METADATA
DATE:'07-07-2001' RESULT:'5-0'
END
```

```
START
TEAM OF 5 PLAYERS
FORMATION
2-1-1
LINEUPNONUM
'El Manco'
'Alves Daniel'
'Pedrito Lopez'
'Gaston Perez'
'Pepito Radiactivo'
SUBSTITUTESNONUM
'La Maquina'
'Pedrito'
END
```

## Requerimientos

Para construir el compilador, se requieren las siguientes dependencias:

* [Bison v3.8.2](https://www.gnu.org/software/bison/)
* [CMake v3.24.1](https://cmake.org/)
* [Flex v2.6.4](https://github.com/westes/flex)
* [GCC v11.1.0](https://gcc.gnu.org/)
* [Make v4.3](https://www.gnu.org/software/make/)

Si en lugar de trabajar con un entorno _Linux_, se está construyendo el proyecto sobre un entorno _Microsoft Windows_, se debe instalar _Microsoft Visual Studio 2022_ con las extensiones para desarrollar aplicaciones en _C/C++_, así como también las herramientas requeridas, con excepción del compilador _GCC_ y la herramienta _Make_.

## Construcción

Para construir el proyecto por completo, ejecute en la raíz del repositorio los siguientes comandos (en _Linux_):

```bash
user@machine:path/ $ chmod u+x --recursive script
user@machine:path/ $ script/build.sh
```

En un entorno _Microsoft Windows_, en cambio, se debe ejecutar:

```bash
user@machine:path/ $ script\build.bat
```

Luego se deberá abrir la solución generada `bin\Compiler.sln` con el IDE _Microsoft Visual Studio 2022_. Los ejecutables que este sistema construye se depositan dentro del directorio `bin\Debug` y `bin\Release`, según corresponda.

## Ejecución

Para compilar un programa, primero cree un archivo vacío denominado `program` (o el nombre que desee), con el siguiente contenido:

```
START
TEAM 'The Red Devils' OF 5 PLAYERS
FORMATION
2-1-1
LINEUP
1: 'El Manco'
2: 'Alves Daniel'
3: 'Pedrito Lopez'
4: 'Gaston Perez'
5: 'Pepito Radiactivo'
SUBSTITUTES
6: 'La Maquina'
7: 'Pedrito'
METADATA
DATE:'07-07-2001' RESULT:'5-0'
END
```

Luego, ejecute el compilador desde el directorio raíz del proyecto, o desde cualquier otro lugar indicando el path hacia el script `start.sh` y pasando por parámetro el path hacia el programa a compilar:

```bash
user@machine:path/ $ script/start.sh program
```

En Windows:

```bash
user@machine:path/ $ script\start.bat program
```

Si el programa se compila sin errores y pasa las verificaciones, se generara un archivo imageGenerator.py dentro de la carpeta output en la raiz del proyecto. 

Esta carpeta output se puede exportar y correr para generar la imagen deseada. 


## Testing

En Linux:

```bash
user@machine:path/ $ script/test.sh
```

En Windows:

```bash
user@machine:path/ $ script\test.bat
```

Si desea agregar nuevos casos de uso, deberá crear un archivo por cada uno, que contenga el programa a testear dentro de las carpetas `test/accept` o `test/reject` según corresponda (es decir, si el mismo debe ser aceptado o rechazado por el compilador).
