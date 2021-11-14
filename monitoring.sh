#!/bin/bash

echo "Architecture & version de kernel:"	
uname -a
echo "Processeurs physiques:"
lscpu | grep 'Socket'
echo "Processeurs virtuels:"
lscpu | grep 'CPU(s):' | sed '2d'
echo 'Mémoire vive:'
free -m
echo 'Utilisation disque:'
df -H
echo 'Utilisation processus:'
top
