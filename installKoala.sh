#!/usr/bin/env bash

sudo -u root -i <<EOF
echo -e "[isra_repo]\nSigLevel= Optional TrustedOnly\nServer = https://israellopezdeveloper.github.io/israel_repo/" >> /etc/pacman.conf
pacman -Syyu --noconfirm
EOF
