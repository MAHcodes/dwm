/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int startwithgaps	    = 1;    	 /* 1 means gaps are used by default */
static const unsigned int gappx     = 10;       /* default gap between windows in pixels */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 0;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const double activeopacity   = 1.0f;     /* Window opacity when it's focused (0 <= opacity <= 1) */
static const double inactiveopacity = 0.6f;   /* Window opacity when it's inactive (0 <= opacity <= 1) */
static       Bool bUseOpacity       = True;     /* Starts with opacity on any unfocused windows */
static const char *fonts[]          = { "JetBrainsMono Nerd Font Mono:size=10" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font Mono:size=10";
static const char col_gray1[]       = "#2e3440";
static const char col_gray2[]       = "#2e3440";
static const char col_gray3[]       = "#81a1c1";
static const char col_gray4[]       = "#2e3440";
static const char col_cyan[]        = "#81a1c1";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeTitle]  = { col_gray3, col_gray4,  col_gray4  },
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
	{ "firefoxdeveloperedition",  NULL,   NULL,         1 << 1,       0,           -1 },
	{ "TelegramDesktop",  NULL,   NULL,         1 << 3,       0,           -1 },
	{ "notion-app-enhanced",  NULL,   NULL,         1 << 6,       0,           -1 },
	{ "Mailspring",  NULL,   NULL,         1 << 7,       0,           -1 },
	{ NULL,       "floating", NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "alacritty", "-t", scratchpadname };

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define SECMODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("alacritty --class floating -e pulsemixer") },
	{ MODKEY,                       XK_n,      spawn,          SHCMD("alacritty --class floating -e ncmpcpp") },
	{ MODKEY,                       XK_backslash,spawn,        SHCMD("alacritty --class floating") },
  { MODKEY,                       XK_F5,      spawn,          SHCMD("feh --bg-fill --randomize --recursive ~/Pictures/Wallpapers/")},
  { MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("hsetroot -solid '#2e3440'")},
  { MODKEY,                       XK_r,      spawn,          SHCMD("rofi -show drun -config ~/.config/rofi/rofidmenu.rasi")},
  { MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD("rofi -show emoji -config ~/.config/rofi/rofidmenu.rasi")},
  { MODKEY|ShiftMask,             XK_c,      spawn,          SHCMD("rofi -show calc -config ~/.config/rofi/rofidmenu.rasi")},
  { MODKEY|ShiftMask,             XK_r,      spawn,          SHCMD("~/.config/rofi/scripts/rofi-beats")},
  { MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("firefox-developer-edition")},
  { MODKEY|ShiftMask,             XK_n,      spawn,          SHCMD("pcmanfm")},
  { MODKEY|ShiftMask,             XK_o,      spawn,          SHCMD("notion-app-enhanced")},
  { MODKEY,                       XK_e,      spawn,          SHCMD("mailspring")},
  { MODKEY|ShiftMask,             XK_d,      spawn,          SHCMD("notify-send -t 3500 \"$(date '+%a %d %b %Y, %H:%M')\" --icon=none") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_a,      toggleopacity,  {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_j,      moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_k,      moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_l,      moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_h,      moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|SECMODKEY,             XK_j,      moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|SECMODKEY,             XK_k,      moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|SECMODKEY,             XK_l,      moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|SECMODKEY,             XK_h,      moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_k,      moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_j,      moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_h,      moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_l,      moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_k,      moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_j,      moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_h,      moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_l,      moveresizeedge, {.v = "R"} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|SECMODKEY,             XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY|SECMODKEY,             XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
  { 0,                            XK_Print,  spawn,          SHCMD("scrot ~/%Y-%m-%d-%T-screenshot.png")},
  { MODKEY,                       XK_Print,  spawn,          SHCMD("flameshot gui")},
  { MODKEY|ShiftMask,             XK_Print,  spawn,          SHCMD("killall flameshot")},
  { MODKEY,                       XK_Escape, spawn,          SHCMD("slock")},
  { MODKEY|ShiftMask,             XK_Escape, spawn,          SHCMD("shutdown -h now")},
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
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

