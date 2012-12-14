#!/bin/sh
# 不清空规则，只允许ICMP通过
iptables -I OUTPUT -j DROP
iptables -A INPUT -p icmp -j ACCEPT  # 将规则插入最上
iptables -I OUTPUT -p icmp -j ACCEPT
# 禁止22端口
iptables -I INPUT -p tcp --dport 22 -j DROP