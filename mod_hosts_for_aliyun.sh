#!/bin/bash
echo "47.94.245.197 api.aliyundrive.com" | sudo tee -a /etc/hosts
echo "47.94.245.197 auth.aliyundrive.com" | sudo tee -a /etc/hosts
echo "121.89.3.30 cn-beijing-data.aliyundrive.net" | sudo tee -a /etc/hosts
sudo apt update
sudo apt install network-manager -y
sudo systemctl restart NetworkManager.service
