#!/bin/bash

# 更新系统
apt-get update

# 安装 iptables
apt-get install -y iptables

# 设置 iptables 规则
iptables -P INPUT ACCEPT
iptables -P FORWARD ACCEPT
iptables -P OUTPUT ACCEPT
iptables -F

# 保存 iptables 规则
iptables-save

# 安装 iptables-persistent 并保存规则
apt-get install -y iptables-persistent
netfilter-persistent save
netfilter-persistent reload

# 复制 authorized_keys 文件
cp /home/ubuntu/.ssh/authorized_keys /root/.ssh/

# 删除 60-cloudimg-settings.conf 文件
rm /etc/ssh/sshd_config.d/60-cloudimg-settings.conf

# 修改 sshd_config 文件以允许 root 登录和密码认证
sed -i 's/^#\?PermitRootLogin.*/PermitRootLogin yes/g' /etc/ssh/sshd_config
sed -i 's/^#\?PasswordAuthentication.*/PasswordAuthentication yes/g' /etc/ssh/sshd_config

# 设置 root 密码
echo "Please enter the new root password:"
read -s root_password
echo "root:${root_password}" | chpasswd

# 重启 sshd 服务
systemctl restart sshd

# 开启 BBR
echo "net.core.default_qdisc=fq" >> /etc/sysctl.conf
echo "net.ipv4.tcp_congestion_control=bbr" >> /etc/sysctl.conf
sysctl -p

# 设置交换分区
curl -O https://raw.githubusercontent.com/WANG-Guangxin/Utils/master/swap.sh && chmod +x swap.sh && ./swap.sh
