#!/bin/bash
set -e

# install VSCode according to https://code.visualstudio.com/docs/setup/linux
sudo apt-get install -y wget gpg
wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
sudo install -o root -g root -m 644 packages.microsoft.gpg /etc/apt/trusted.gpg.d/
sudo sh -c 'echo "deb [arch=amd64,arm64,armhf signed-by=/etc/apt/trusted.gpg.d/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" > /etc/apt/sources.list.d/vscode.list'
rm -f packages.microsoft.gpg

sudo apt install -y apt-transport-https
sudo apt update
sudo apt install -y code

# Ubuntu development deps
sudo apt install -y \
build-essential \
cmake \
g++ \
git \
ninja-build \
pkg-config \
tar \
unzip \
zip \
curl

# Install up-to-date CMake (https://apt.kitware.com/)
CODE_NAME=`lsb_release -cs`
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null
echo "deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ ${CODE_NAME} main" | sudo tee /etc/apt/sources.list.d/kitware.list >/dev/null
sudo apt-get update
sudo apt-get install kitware-archive-keyring
sudo apt-get install cmake

# Install Clang last since it isn't strictly needed
sudo apt install -y clang

echo "C++ template development environment install done"
