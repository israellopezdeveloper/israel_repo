/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMonoMedium Nerd Font:size=12:antialias=true:autohint=true" };
static const char dmenufont[]       = "JetBrainsMonoMedium Nerd Font:size=12:antialias=true:autohint=true";
static const char material_bg[]       = "#0f101a";
static const char window_border[]       = "#000000";
static const char inactive[]       = "#4c566a";
static const char active[]       = "#ffffff";
static const char material_focus[]        = "#a151d3";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { inactive, material_bg, window_border },
	[SchemeSel]  = { active, material_focus,  material_focus  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "₿", "", "" };
static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const int momentaryalttags = 0; /* 1 means alttags will show only when key is held down*/

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"
#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "﩯",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
	{ "",      grid },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
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

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", material_bg, "-nf", inactive, "-sb", material_focus, "-sf", active, NULL };
static const char *termcmd[]  = { "kitty", NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
  // ------------------ Windows ------------------

  // Switch between windows
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },

  // Change window sizes
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },

  // Toggle floating
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

  // Toggle bar
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },

  // Move windows in current stack
  { MODKEY|ShiftMask, XK_j, rotatestack, {.i = +1 } },
  { MODKEY|ShiftMask, XK_k, rotatestack, {.i = -1 } },
  
  // Focus next - prev monitor
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },

  // Send window to next - prev monitor
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

  // Kill window
	{ MODKEY,                       XK_w,      killclient,     {0} },

  // Restart dwm
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} },

  // Quit dwm
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

  // Shutdown system
  { MODKEY|ControlMask,           XK_h,      spawn,          SHCMD("shutdown now") },

  // Reboot system
  { MODKEY|ControlMask,           XK_r,      spawn,          SHCMD("reboot") },

  // ---------------- Workspaces -----------------
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

  // ------------------- Apps --------------------

  // dmenu
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = dmenucmd } },

  // rofi
  { MODKEY,                       XK_m,      spawn,          SHCMD("rofi -show drun") },

  // Window nav (rofi)
  { MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD("rofi -show") },

  // Terminal
  { MODKEY,                       XK_Return, spawn,          SHCMD("kitty") },

  // File explorer
  { MODKEY,                       XK_e,      spawn,          SHCMD("kitty --title 'File Explorer' zsh -c ranger") },

  // Browser
  { MODKEY,                       XK_b,      spawn,          SHCMD("brave") },

  // Redshift
  //{ MODKEY,                       XK_r,      spawn,          SHCMD("redshift -O 2400") },
  //{ MODKEY|ShiftMask,             XK_r,      spawn,          SHCMD("redshift -x") },

  // Screenshot
  { MODKEY,                       XK_s,      spawn,          SHCMD("spectacle") },

  // ----------------- Hardware ------------------

  // Volume
  {0,                             XF86XK_AudioLowerVolume, spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%")},
  {0,                             XF86XK_AudioRaiseVolume, spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%")},
  {0,                             XF86XK_AudioMute,        spawn, SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle")},

  // Brightness
  {0,                             XF86XK_MonBrightnessUp,  spawn, SHCMD("brightnessctl set +10%")},
  {0,                             XF86XK_MonBrightnessDown,spawn, SHCMD("brightnessctl set 10%-")},

  // Factorial ratio
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },

  // Select layout
	{ MODKEY|Mod1Mask,              XK_1,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|Mod1Mask,              XK_2,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|Mod1Mask,              XK_3,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|Mod1Mask,              XK_4,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|Mod1Mask,              XK_5,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|Mod1Mask,              XK_0,      setlayout,      {0} },

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

  // Alternative tags
	{ MODKEY,                       XK_n,      togglealttag,   {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


