#!/bin/bash

set -e

pacman -Syyu --noconfirm wget git 

sfdisk --no-reread --force /dev/sda < /vagrant/new-config

btrfs filesystem resize max /

#wget -O - https://israellopezdeveloper.github.io/israel_repo/installKoala.sh | bash <(cat) </dev/tty
