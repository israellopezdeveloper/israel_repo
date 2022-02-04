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
makepkg -si
cd ..
rm rf trizen

trizen --sudo_remove_timestamp=0 --sudo_autorepeat=1 --sudo_autorepeat_at_runtime=1 -Syyu --noconfirm brave-bin nerd-fonts-complete koala-dwm
