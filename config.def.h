/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static const unsigned int barborderpx = 3;		/* border on the bar with active monitor */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 20;       /* vertical padding of bar */
static const int sidepad            = 20;       /* horizontal padding of bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "SourceCodePro:size=15" };
static const char dmenufont[]       = "monospace:size=10";
/* static const char col_gray1[]       = "#222222"; */
/* static const char col_gray2[]       = "#444444"; */
/* static const char col_gray3[]       = "#bbbbbb"; */
/* static const char col_gray4[]       = "#eeeeee"; */
/* static const char col_cyan[]        = "#005577"; */

static const char * const sunset_palette[] = {
	"#e4907f",
	"#461120",
	"#fbd29c",
	"#853339",
	"#a6493c",
	"#2b2237",
	"#403158"
};

static const char * const purple_palette[] = {
	"#884b64",
	"#3b343c",
	"#cb608b",
	"#4f4854",
	"#5b3e53",
	"#2b2237",
	"#8c8c8d"
};

static const char * const monochrome_palette[] = {
	"#dddddd",
	"#3b343c",
	"#dddddd",
	"#1f1814",
	"#080808",
	"#080808",
	"#8c8c8d"
};

#define SELECTED_PALETTE monochrome_palette

static const char bright_gold[] = "#f4d897";
static const char darkish_gray[] = "#4b4237";
static const char darker_gray[] = "#2b1217";
static const char bright_gray[] = "#ede7d9";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { SELECTED_PALETTE[0], SELECTED_PALETTE[5], SELECTED_PALETTE[5] },
	[SchemeSel]  = { SELECTED_PALETTE[4], SELECTED_PALETTE[2], SELECTED_PALETTE[2] },
	[SchemeHid]  = { SELECTED_PALETTE[3], SELECTED_PALETTE[2], SELECTED_PALETTE[3] },
	[SelectedMon] = { SELECTED_PALETTE[4], SELECTED_PALETTE[6], SELECTED_PALETTE[6] }
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	/* { "Gimp",     NULL,       NULL,       0,            1,           -1 }, */
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Alacritty",  NULL,  "Note editor", 0,	        1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const int lpm[] = {
        /* Index of preferred layout], if LENGTH(lpm)<#monitors -> default layout */
        0, 0, 3,
};

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL }; */
static const char *roficmd[] = { "rofi", "-show", "run", "-theme", "~/.config/rofi/style.rasi", "-monitor", "-4" ,NULL };
static const char *termcmd[] = { "alacritty", NULL };

static const char takenote[] = "~/.config/scripts/takenote.sh";
static const char opennote[] = "~/.config/scripts/opennote.sh";

/* Multimedia controls */
static const char *pausetrack[] = { "playerctl", "play-pause", NULL };
static const char *nexttrack[] = { "playerctl", "next", NULL };
static const char *prevtrack[] = { "playerctl", "previous", NULL };

/* Brightness control keys */
static const char *brightnessup[] = { "brightnessctl", "s", "+10%", NULL };
static const char *brightnessdown[] = { "brightnessctl", "s", "10%-", NULL };

/* Saving screenshots to clipboard */
static const char screenshottoclipboard[] = "maim --select | xclip -selection clipboard -t image/png";

#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,		   {.v = roficmd} },
	{ MODKEY,					    XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstackvis,  {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstackvis,  {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      focusstackhid,  {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      focusstackhid,  {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_Tab,       shiftviewclients, { .i = +1 } },
	{ MODKEY|ShiftMask,             XK_backslash, shiftviewclients, { .i = -1 } },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,						XK_c,	   gotocleartag,   {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	/* { MODKEY,                       XK_s,      show,           {0} }, */
	{ MODKEY,             XK_s,      showall,        {0} },
	{ MODKEY|ShiftMask,             XK_h,      hide,           {0} },
	{ 0,				XF86XK_AudioPlay,      spawn,          {.v = pausetrack} },
	{ 0,				XF86XK_AudioNext,      spawn,          {.v = nexttrack} },
	{ 0,				XF86XK_AudioPrev,      spawn,          {.v = prevtrack} },
	{ 0,				XF86XK_MonBrightnessUp,      spawn,          {.v = brightnessup} },
	{ 0,				XF86XK_MonBrightnessDown,      spawn,          {.v = brightnessdown} },
	{ MODKEY|ShiftMask,             XK_s,      spawn,		   SHCMD(screenshottoclipboard) },
	{ MODKEY,			            XK_n,      spawn,		   SHCMD(takenote) },
	{ MODKEY|ShiftMask,             XK_n,      spawn,		   SHCMD(opennote) },
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
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
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

