#!/usr/bin/env bash

sudo -u root passwd

sudo -u root -i <<EOF
echo -e "[isra_repo]\nSigLevel= Optional TrustedOnly\nServer = https://israellopezdeveloper.github.io/israel_repo/" >> /etc/pacman.conf
pacman -Syyu --noconfirm koala-base
useradd -m -g users -G audio,lp,optical,storage,video,wheel,games,power,scanner -s /bin/zsh israel
EOF

sudo -u root passwd israel

git clone https://aur.archlinux.org/trizen.git
cd trizen
makepkg -si --noconfirm
cd ..
rm rf trizen

sudo -u root mount -o remount,size=10G,noatime /tmp
sudo -u root -i <<EOF
pacman -Syyu --noconfirm koala-dwm
EOF
