#!/bin/sh

# 清空所有规则
sudo iptables -t filter -F
# 只开放22端口
sudo iptables -t filter -A INPUT -p tcp --dport 22 -j ACCEPT
sudo iptables -t filter -A OUTPUT -p tcp --sport 22 -j ACCEPT
# 禁止发送ICMP包
sudo iptables -t filter -A OUTPUT -p icmp -j DROP
# INPUT默认规则为DROP
sudo iptables -t filter -P INPUT DROP
# OUTPUT默认规则为ACCEPT
sudo iptables -t filter -P OUTPUT ACCEPT
# FORWARD默认规则为DROP
sudo iptables -t filter -P FORWARD DROP

# 保存设置
# sudo iptables-save -c > $HOME/iptables.save
# 载入设置
# sudo iptables-restore < $HOME/iptables.save