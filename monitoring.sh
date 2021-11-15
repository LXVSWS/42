#!/bin/bash
arch=$(uname -a)
cpu=$(lscpu | grep 'Socket' | tail -c2)
cpu0=$(lscpu | grep '(s)' | sed -n '2p' | tail -c2)
ram=$(free -m | awk '$1 == "Mem:" {print $4}')
ram0=$(free | awk '$1 == "Mem:" {printf("%.2f"), $3/$2*100}')
disk=$(df -Bg | sed -n '4p' | awk '{print $4}')
disk0=$(df -Bg | sed -n '4p' | awk '{print($5)}')
cpu1=$(top -bn1 | awk '$1 == "%Cpu(s):" {print $2}')
boot=$(who -b | awk '{printf $3" "$4}')
lvm=$(lsblk | grep 'lvm' | wc -l)
lvm0=$(if [ $lvm -eq 0 ] ; then echo Non ; else echo Oui ; fi)
tcp=$(cat /proc/net/sockstat | awk '$1 == "TCP:" {print $3}')
tcp0=$(cat /proc/net/sockstat{,6} | awk '$1 == "TCP6:" {print $3}')
tcp1=$(( $tcp + $tcp0 ))
users=$(users | wc -w)
ip=$(hostname -I | awk '{print $1}')
mac=$(ip l | sed -n '4p' | awk '{print $2}')
cmd=$(journalctl _COMM=sudo | grep 'COMMAND' | wc -l)
wall "
- Architecture: $arch
- Processeur(s) physique(s): $cpu
- Processeur(s) virtuel(s): $cpu0
- Mémoire vive disponible: ${ram}MB (taux d'utilisation: $ram0%)
- Mémoire de masse disponible: ${disk}b (taux d'utilisation: $disk0)
- Taux d'utilisation processeur(s): $cpu1%
- Dernier démarrage système: $boot
- LVM actif: $lvm0
- Connexion(s) active(s): $tcp1
- Utilisateur(s) actif(s): $users
- Adresse IPv4: $ip
- Adresse MAC: $mac
- Commande sudo utilisée $cmd fois
"
