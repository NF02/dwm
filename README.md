# dwm
È un fork di <a href="dwm.suckless.org">dwm</a> con delle patch e delle 
personalizzazioni, viene utilizzato all'interno della 
<a href="https://github.com/NF02/dotfiles">mia configurazione</a>
```
                           +------+----------------------------------+--------+
                           | tags | title                            | status +
                           +------+---------------------+------------+--------+
                           |                            |                     |
                           |                            |                     |
                           |                            |                     |
                           |                            |                     |
                           |          master            |        stack        |
                           |                            |                     |
                           |                            |                     |
                           |                            |                     |
                           |                            |                     |
                           +----------------------------+---------------------+
```
## patch applicate
- <a href="https://dwm.suckless.org/patches/bottomstack/">bottomstack</a>;
- <a href="https://dwm.suckless.org/patches/fullscreen/">fullscreen</a>;
- <a href="https://dwm.suckless.org/patches/centeredmaster/">centeredmaster</a>
## Modifiche
le modifiche implementate sono le seguenti:
- Ho rimosso un if che lo portava al crush nel caso degli emoji
  perché il software per filosofia è estremamente minimalista e
  non accetta alcuni carattere speciali.
- Ho creato la cartella *lib* e all'interno sono contenute tre librerie
    - keyWorld.h - al suo interno vengono mappati tutti i tasti dei
    <a href="https://en.wikipedia.org/wiki/ThinkPad_T_series">Thinkpad della serie T</a>;
    - command.h - contiene la maggioranza dei comandi che vengono eseguiti con le shortcuts;
- Ho disattivato il resizehints.
## Layout
### tile []=
Mod-t
```
+----------+------+
|          |      |
|          +------+
|          |      |
|          +------+
|          |      |
+----------+------+

```
### monocle [M]
Mod-m
```
+-----------------+
|                 |
|                 |
|                 |
|                 |
|                 |
|                 |
+-----------------+
```
### bstack (TTT)
Mod-o
```
+-----------------+
|                 |
|                 |
|                 |
+-----+-----+-----+
|     |     |     |
|     |     |     |
+-----+-----+-----+
```
### bstackhoriz (===)
Mod-u
```
+-----------------+
|                 |
|                 |
|                 |
+-----------------+
+-----------------+
+-----------------+
+-----------------+
```
### centeredmaster layout |M|
Mod-Shift-u
```
+------------------------------+       +------------------------------+
|+--------++--------++--------+|       |+--------++--------++--------+|
||        ||        ||        ||       ||        ||        ||        ||
||        ||        ||        ||       ||        ||   M1   ||        ||
||        ||        ||        ||       ||        ||        ||        ||
||  S2    ||   M    ||   S1   ||       ||        |+--------+|        ||
||        ||        ||        ||       ||        |+--------+|        ||
||        ||        ||        ||       ||        ||        ||        ||
||        ||        ||        ||       ||        ||   M2   ||        ||
||        ||        ||        ||       ||        ||        ||        ||
|+--------++--------++--------+|       |+--------++--------++--------+|
+------------------------------+       +------------------------------+
```
### centeredfloatingmaster >M>
Mod-Shift-o
```
+------------------------------+       +------------------------------+
|+--------++--------++--------+|       |+--------++--------++--------+|
||        ||        ||        ||       ||        ||        ||        ||
||    +------------------+    ||       ||    +--------++--------+    ||
||    |                  |    ||       ||    |        ||        |    ||
||    |                  |    ||       ||    |        ||        |    ||
||    |        M         |    ||       ||    |   M1   ||   M2   |    ||
||    |                  |    ||       ||    |        ||        |    ||
||    +------------------+    ||       ||    +--------++--------+    ||
||        ||        ||        ||       ||        ||        ||        ||
|+--------++--------++--------+|       |+--------++--------++--------+|
+------------------------------+       +------------------------------+
```
## Installazione
make && sudo make install
