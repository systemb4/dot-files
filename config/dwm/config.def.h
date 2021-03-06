/* dwm config */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx       = 1;        /* border pixel of windows */
static const unsigned int snap           = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;        /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;        /* systray spacing */
static const int systraypinningfailfirst = 1;        /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;        /* 0 means no systray */
static const int showbar                 = 1;        /* 0 means no bar */
static const int topbar                  = 1;        /* 0 means bottom bar */
static const char *fonts[]               = { "monospace:size=16" };
static const char dmenufont[]            = "monospace:size=14";
static const char col_gray1[]            = "#222222";
static const char col_gray2[]            = "#444444";
static const char col_gray3[]            = "#bbbbbb";
static const char col_gray4[]            = "#eeeeee";
static const char col_main[]             = "#005577";
static const char col_border[]           = "#005577";
static const char *colors[][3]           = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_main,  col_border  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Sxiv",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "[M]",      monocle },
    { "><>",      NULL },    /* no layout function means floating behavior */
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

static Key keys[] = {
    /* modifier                     key        function        argument */
    // applications and scripts
    { MODKEY,                       XK_p,      spawn,          SHCMD("dmenu_run -i -p run:") },
    { 0,                   XF86XK_Search,      spawn,          SHCMD("dmenu_run -i -p run:") },
    { MODKEY,                  XK_Return,      spawn,          SHCMD("$TERMINAL") },
    { MODKEY,                       XK_w,      spawn,          SHCMD("$BROWSER") },
    { MODKEY,                       XK_a,      spawn,          SHCMD("$TERMINAL -e pulsemixer") },
    { MODKEY,                       XK_f,      spawn,          SHCMD("$TERMINAL -e vifm") },
    { MODKEY,                      XK_F2,      spawn,          SHCMD("scrot -e 'mv $f ~/media/pictures/scrots/'") },
    { MODKEY,                       XK_i,      spawn,          SHCMD("display_prompt.sh") },
    { MODKEY|ShiftMask,             XK_i,      spawn,          SHCMD("xset r rate 300 50") },
    { MODKEY,                       XK_s,      spawn,          SHCMD("dwm_system.sh") },
    { MODKEY,                   XK_grave,      spawn,          SHCMD("clipmenu") },
    { MODKEY|ShiftMask,         XK_grave,      spawn,          SHCMD("dmenu_emoji.sh") },
    { MODKEY,                      XK_F8,      spawn,          SHCMD("qrcode.sh") },
    { MODKEY,                      XK_F7,      spawn,          SHCMD("ffplay /dev/video0") },
                            
    // media controls
    { MODKEY,                       XK_u,      spawn,          SHCMD("amixer set Master 5%+") },
    { 0,         XF86XK_AudioRaiseVolume,      spawn,          SHCMD("amixer set Master 5%+") },
    { 0,         XF86XK_AudioLowerVolume,      spawn,          SHCMD("amixer set Master 5%-") },
    { MODKEY,                       XK_d,      spawn,          SHCMD("amixer set Master 5%-") },
    { MODKEY,                       XK_o,      spawn,          SHCMD("amixer set Master toggle") },
    { 0,                XF86XK_AudioMute,      spawn,          SHCMD("amixer set Master toggle") },
    { MODKEY|ShiftMask,             XK_o,      spawn,          SHCMD("amixer set Master 0 && amixer set Master off") },
    { MODKEY,                      XK_F9,      spawn,          SHCMD("amixer set Capture toggle") },
    { 0,             XF86XK_AudioMicMute,      spawn,          SHCMD("amixer set Capture toggle") },
    { 0,          XF86XK_MonBrightnessUp,      spawn,          SHCMD("xbacklight -inc 10") },
    { MODKEY|ShiftMask,             XK_u,      spawn,          SHCMD("xbacklight -inc 10") },
    { 0,        XF86XK_MonBrightnessDown,      spawn,          SHCMD("xbacklight -dec 10") },
    { MODKEY|ShiftMask,             XK_d,      spawn,          SHCMD("xbacklight -dec 10") },
    { MODKEY,                     XK_F12,      spawn,          SHCMD("playerctl next") },
    { 0,                XF86XK_AudioNext,      spawn,          SHCMD("playerctl next") },
    { MODKEY,                     XK_F11,      spawn,          SHCMD("playerctl play-pause") },
    { 0,                XF86XK_AudioPlay,      spawn,          SHCMD("playerctl play-pause") },
    { MODKEY,                     XK_F10,      spawn,          SHCMD("playerctl previous") },
    { 0,                XF86XK_AudioPrev,      spawn,          SHCMD("playerctl previous") },
                                                                                                        
    // basics
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,         XK_equal,      incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask,         XK_minus,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.01 } },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.01 } },
    { MODKEY,               XK_backslash,      setmfact,       {.f = 1.55 } },
    { MODKEY|ShiftMask,     XK_backslash,      setmfact,       {.f = 1.50 } },
    { MODKEY|ShiftMask,        XK_Return,      zoom,           {0} },
    { MODKEY,                     XK_Tab,      view,           {0} },
    { MODKEY,                       XK_q,      killclient,     {0} },
    { MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
    { MODKEY|ShiftMask,         XK_space,      setlayout,      {0} },
    { MODKEY,                   XK_space,      togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY|ShiftMask,     XK_BackSpace,      quit,           {0} },

    // toggle and swap between monitors
    { MODKEY,               XK_semicolon,      focusmon,       {.i = -1 } },
    { MODKEY,              XK_apostrophe,      focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,     XK_semicolon,      tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,    XK_apostrophe,      tagmon,         {.i = +1 } },

    // toggle layouts
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_n,      setlayout,      {.v = &layouts[2]} },

    // toggle tags
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          SHCMD("$TERMINAL") },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
