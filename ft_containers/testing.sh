#!/bin/bash

WHITE='\033[1;37m'
RED='\033[0;31m'
GREEN='\033[0;32m'
CYAN='\033[0;96m'
YELLOW='\033[0;93m'
BLUE='\033[1;34m'
RESET='\033[0m'

ft()
{
    cat main.cpp | sed 's/using namespace std/using namespace ft/g' | sed 's/namespace std/namespace ft/g' > tmp.cpp
    rm main.cpp
    mv tmp.cpp main.cpp
}

std()
{
    cat main.cpp | sed 's/using namespace ft/using namespace std/g' | sed 's/namespace ft/namespace std/g' > tmp.cpp
    rm main.cpp
    mv tmp.cpp main.cpp
}

clear
clean=$(make fclean)
make=$(make)
std
test=$(make test)
ft
printf "${WHITE}FT_CONTAINERS TESTER |\n_____________________|${RESET}\n"
printf "\n${YELLOW}CONSTRUCTOR${RESET} | "
diff=$(diff <(./ft_containers 0) <(./std_containers 0))
if [ -z "$diff" ]
then
printf "${GREEN}DIFF OK${RESET} \xE2\x9C\x85"
else
printf "${RED}DIFF KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT TIMER : ${RESET}"
./ft_containers 1
printf "${BLUE}STD TIMER : ${RESET}"
./std_containers 1
sleep 1
printf "\n${YELLOW}OPERATOR=${RESET} | "
diff=$(diff <(./ft_containers 2) <(./std_containers 2))
if [ -z "$diff" ]
then
printf "${GREEN}DIFF OK${RESET} \xE2\x9C\x85"
else
printf "${RED}DIFF KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT TIMER : ${RESET}"
./ft_containers 3
printf "${BLUE}STD TIMER : ${RESET}"
./std_containers 3
sleep 1
