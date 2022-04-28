/* appearance */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 15;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */

static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const char panel[][20]       = { "xfce4-panel", "Xfce4-panel" }; /* name & cls of panel win */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10", "JoyPixels:pixelsize=11;antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=10";

/* colors */
static const char normbgcolor[]     = "#222222";
static const char normbordercolor[] = "#444444";
static const char normfgcolor[]     = "#bbbbbb";
static const char selfgcolor[]      = "#770000";
static const char selbordercolor[]  = "#eeeeee";
static const char selbgcolor[]      = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor, selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ panel[1],   NULL,       NULL,       (1 << 9) - 1, 1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "lib/layout.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "TTT",      bstack },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "DD",       doubledeck },
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }
#define TERMCMD(cmd) { .v = (const char*[]){ "st", "-e", cmd, NULL } }


/* terminal */
#define TERM "st"
#define TMUX "st -e tmux"


#include "lib/command.h"
#include "lib/keyWorld.h"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_Insert, spawn,	   {.v = clipcmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ControlMask,           XK_t,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY|ControlMask,           XK_f,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY|ControlMask,           XK_m,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY,                       XK_Print,  spawn,          {.v = screenshot } },
	{ 0,                            XF86ScreenSaver, spawn,    SHCMD("xscreensaver-command -lock") },
	{ 0,                            XF86MonBrightnessDown, spawn, {.v = cmdbrightnessdown } },
	{ 0,                            XF86MonBrightnessUp, spawn, {.v = cmdbrightnessup } },
	{ 0,                            XF86AudioMute, spawn, {.v = cmdsoundtoggle } },
	{ 0,                            XF86AudioRaiseVolume, spawn, {.v = cmdsoundup } },
	{ 0,                            XF86AudioLowerVolume, spawn, {.v = cmdsounddown } },
	{ 0,                            XF86AudioMicMute, spawn,	{.v = cmdMicOff } },
	{ 0,                            XF86Display,			spawn,		{.v = screenSwitch } },
	{ 0,                            XF86AudioNext,			spawn,		SHCMD("playerctl next") },
	{ 0,                            XF86AudioPause,			spawn,		SHCMD("playerctl pause") },
	{ 0,                            XF86AudioPlay,			spawn,		SHCMD("playerctl play") },
	{ 0,                            XF86AudioStop,			spawn,		SHCMD("playerctl stop") },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	/* gaps command */
	{ MODKEY,                       XK_z,      incrgaps,       {.i = +3 } },
	{ MODKEY|ShiftMask,             XK_z,      incrgaps,       {.i = -3 } },
	{ MODKEY,                       XK_x,      incrogaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_x,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	/* app launcher */
	{ MODKEY,                       XK_F1,     spawn,          TERMCMD("ranger") },
	{ MODKEY,                       XK_F5,     spawn,          {.v = emojicmd } },
	{ MODKEY,                       XK_F6,     spawn,          {.v = Webcmd } },
	{ MODKEY,                       XK_F7,     spawn,          {.v = Impcmd } },
	{ MODKEY,                       XK_F8,     spawn,          {.v = Telegramcmd } },
	{ MODKEY,                       XK_F9,     spawn,          {.v = touchpadcmd } },
	{ MODKEY,                       XK_F10,    spawn,          {.v = Discordcmd } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ Mod1Mask|ShiftMask,           XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

