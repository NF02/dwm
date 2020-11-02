# dwm
It is a fork of <a href="dwm.suckless.org"> dwm </a> with patches and
customizations, is used within the
<a href="https://github.com/NF02/dotfiles"> my configuration </a>
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
## patch 
- <a href="https://dwm.suckless.org/patches/bottomstack/">bottomstack</a>;
- <a href="https://dwm.suckless.org/patches/fullscreen/">fullscreen</a>;
- <a href="https://dwm.suckless.org/patches/centeredmaster/">centeredmaster</a>;
- <a href="https://dwm.suckless.org/patches/fibonacci/">fibonacci</a>;
- <a href="https://dwm.suckless.org/patches/xrdb/">xrdb-pywal</a>;
- <a href="https://dwm.suckless.org/patches/vanitygaps/">vanitygaps</a>.
## Changes
the changes implemented are the following:
- I removed an if that led to crush in the case of emojis
   because philosophy software is extremely minimalist e
   it does not accept any special characters.
- I created the *lib* folder and it contains three libraries
     - keyWorld.h - all the keys are mapped into it
     <a href="https://en.wikipedia.org/wiki/ThinkPad_T_series">T-series Thinkpad</a>;
     - command.h - contains most of the commands that are executed with shortcuts;
- I have deactivated the resizehints option in config.h.
``` C++
/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
```
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
### fibonacci layout
#### spiral [@]
Mod-n
```
+-----------+-----------+ 
|           |           |
|           |     2     |
|           |           |
|     1     +--+--+-----+
|           | 5|-.|     |
|           +--+--+  3  |
|           |  4  |     |
+-----------+-----+-----+
```
#### dwindle [\\]
Mod-Shoft-n
```
+-----------+-----------+
|           |           |
|           |     2     |
|           |           |
|     1     +-----+-----+
|           |     |  4  |
|           |  3  +--+--+
|           |     | 5|-.|
+-----------+-----+-----+
```
## Requirements
- <a href="https://github.com/NF02/st">ST</a>;
- <a href="https://github.com/NF02/dmenu">dmenu</a>.

## Installation
make && sudo make install

## Attention: in the case of Emojis or special characters
In case st has a crask or does not display the fonts, install the <a href="https://aur.archlinux.org/packages/libxft-bgra/">libxft-bgra</a> present in the AUR.
