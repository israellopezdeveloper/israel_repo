#!/bin/bash

set -e

pacman -Syyu --noconfirm wget git 

sfdisk --no-reread --force /dev/sda < /vagrant/new-config

btrfs filesystem resize max /
