[English](README.md)        [Русский](README_Russian.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Prime World Trailer](PW_trailer.png)](https://youtu.be/Fkd-zva4npI)
[Prime World](https://wikipedia.org/wiki/Prime_World) es un juego multijugador de arena de batalla en línea (MOBA) lanzado en 2014. El juego fue desarrollado en un motor propio por la empresa [Nival](http://nival.com/), escrito principalmente en C++.

El juego consta de dos partes: Castillo y Batalla. El jugador asume el papel de Lord o Lady. En el Castillo, el jugador construye edificios, contrata Héroes y selecciona Talentos para ellos. En la parte de Batalla, el jugador controla a un Héroe y utiliza Talentos para luchar contra otros jugadores en batallas por equipos.

En 2024, el código fuente de la parte de Batalla del juego se liberó bajo una [licencia especial](LICENSE.md), que prohíbe el uso comercial pero está completamente abierta para la comunidad de jugadores, el estudio y la investigación.
Por favor, lea cuidadosamente los términos del [acuerdo de licencia](LICENSE.md) antes de usar.

## Qué contiene este repositorio
- `pw` — el código principal de la parte de batalla
- `pw_publish` — cliente compilado de la parte de batalla con códigos de trucos y editor de cliente
- `pw/branches/r1117/Bin/PF_Editor.exe` — editor de datos del juego

## Preparación
Debes descargar los datos de este repositorio y fusionar la carpeta `Bin` con los datos principales del juego. Así es como se hace:

1. Copia la carpeta `pw_publish/branch/Client/PvP/Bin` a `pw/branches/r1117`, reemplazando los archivos existentes.
2. Ejecuta el cliente con los códigos de trucos `pw/branches/r1117/Bin/PW_Game.exe`.
3. Si todo está correcto, verás la ventana de carga, pero sin imagen y con pantalla negra.
4. En la carpeta `Profiles -> game.cfg`, cambia el valor de `local_game 0` a `local_game 1`.
5. Ejecuta el cliente con los códigos de trucos. Ahora deberías ver el lobby donde puedes seleccionar el mapa, héroe y comenzar la batalla.
6. En el juego, presiona la tecla Tilde (~) en el teclado y verás la consola para ingresar códigos de trucos.

Si ocurre algún error, revisa los archivos de registro en `pw/branches/r1117/Bin/logs`.

## Datos del juego
Los datos se pueden editar mediante el editor y se encuentran en `pw/branches/r1117/Data`

Editando los datos, puedes:
1. Cambiar descripciones de talentos y habilidades de héroes.
2. Modificar talentos y habilidades de héroes.
3. Cambiar la lógica de los súbditos y las torres.
4. Añadir nuevos héroes y habilidades.
5. Añadir nuevos talentos.
6. Modificar y agregar efectos.
7. Modificar y agregar modelos y animaciones.

Al modificar datos, no es necesario compilar un nuevo cliente a partir del código. Simplemente presiona `File -> Save`, y todos los cambios aparecerán instantáneamente en el cliente del juego `PW_Game`. Por ejemplo, puedes intentar cambiar la descripción de un talento o habilidad de un héroe.

## Editor de datos del juego
El editor de datos del juego se encuentra en `pw/branches/r1117/Bin/PF_Editor.exe`

Al abrir el editor por primera vez, necesitas configurar la ruta a `Data`:
1. `Tools -> File System Configuration`.
2. `Add -> WinFileSystem`.
3. Establece la carpeta Data como la raíz del sistema: `pw/branches/r1117/Data`.
4. Cierra las ventanas.
5. En el editor: `Views -> Object Browser` y `Views -> Properties Editor`. Estos son los dos paneles principales para editar datos.

Las pestañas del editor pueden moverse y anclarse.

## Cliente del juego con códigos de trucos
En el repositorio puedes encontrar el cliente del juego ya compilado con códigos de trucos `pw_publish/branch/Client/PvP/Bin/PW_Game.exe`

Es necesario que las carpetas `Localization`, `Profiles` y `Data` se encuentren junto a la carpeta `Bin`. Por eso, durante la preparación debes moverlo a la carpeta `pw`. Si se modifica el código, será necesario recompilar el cliente.

## Cómo iniciar PvP
1. En `Profiles -> game.cfg` cambia `local_game 0`.
2. Agrega `login_adress <server address>`.
3. Inicia el juego con el parámetro `-dev_login MiApodo`.

## Cómo iniciar el juego con bots
1. Renombra el archivo `Profiles -> private.cfg_example` a `private.cfg`.
2. Abre el archivo con el bloc de notas.
3. Busca `AT BEGINNING GAME`.
4. Inserta una nueva línea: `add_ai bots` — esto asigna un bot de IA para cada héroe en la partida.

## Solución de posibles errores
1. Renombra el archivo `Profiles -> private.cfg_example` a `private.cfg`.
2. Abre el archivo con el bloc de notas.
3. Busca la sección `performance section`.
4. Encuentra la línea `setvar gfx_fullscreen = 0` — esto hará que el juego se inicie en modo ventana, lo cual puede ser más estable.
5. Otras configuraciones de optimización también se pueden cambiar en la sección `performance section`.

## Agradecimientos
A la comunidad de **Prime World: Nova** por su aporte en la documentación y la corrección de errores.
