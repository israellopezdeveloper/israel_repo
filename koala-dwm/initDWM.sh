#!/bin/sh

wal -i ~/.wallpaper &
dwmblocks &
export _JAVA_AWT_WM_NONREPARENTING=1
export AWT_TOOLKIT=MToolkit 
wmname LG3D
dwm
