
Debian
====================
This directory contains files used to package lksd/lks-qt
for Debian-based Linux systems. If you compile lksd/lks-qt yourself, there are some useful files here.

## lks: URI support ##


lks-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install lks-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your lks-qt binary to `/usr/bin`
and the `../../share/pixmaps/lks128.png` to `/usr/share/pixmaps`

lks-qt.protocol (KDE)

