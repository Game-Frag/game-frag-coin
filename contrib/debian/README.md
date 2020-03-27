
Debian
====================
This directory contains files used to package gamefragd/gamefrag-qt
for Debian-based Linux systems. If you compile gamefragd/gamefrag-qt yourself, there are some useful files here.

## gamefrag: URI support ##


gamefrag-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install gamefrag-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your gamefrag-qt binary to `/usr/bin`
and the `../../share/pixmaps/gamefrag128.png` to `/usr/share/pixmaps`

gamefrag-qt.protocol (KDE)

