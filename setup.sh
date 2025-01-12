#!/bin/bash

# Update and upgrade the system
sudo apt update && sudo apt upgrade -y
# Install zsh, git, wget, and curl
sudo apt install -y zsh git wget curl vim

# Install Visual Studio Code (.deb)
wget -O vscode.deb https://go.microsoft.com/fwlink/?LinkID=760868
sudo dpkg -i vscode.deb
sudo apt install -f -y # Install dependencies if any are missing
rm vscode.deb

# Install Google Chrome (.deb)
wget -O chrome.deb https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
sudo dpkg -i chrome.deb
sudo apt install -f -y # Install dependencies if any are missing
rm chrome.deb

# Generate SSH key for GitHub
echo "Generating SSH key for GitHub..."
ssh-keygen -t ed25519 -C "khalilsohail24@gmail.com" -f ~/.ssh/id_ed25519 -N ""
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519
echo "Your SSH public key is:"
cat ~/.ssh/id_ed25519.pub
echo "Add this key to your GitHub account: https://github.com/settings/keys"


echo "Installation and setup complete!"
