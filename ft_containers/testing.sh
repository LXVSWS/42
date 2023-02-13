#!/bin/bash

WHITE='\033[1;37m'
RED='\033[0;31m'
GREEN='\033[0;32m'
CYAN='\033[0;96m'
YELLOW='\033[0;93m'
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
printf "\n${CYAN}FT VERSION :${RESET}\n"
./ft_containers
printf "\n${YELLOW}STD VERSION :${RESET}\n"
./std_containers
diff=$(diff <(./ft_containers) <(./std_containers))
if [ -z "$diff" ]
then
printf "\n${GREEN}DIFF OK${RESET} \xE2\x9C\x85 \n\n"
else
printf "\n${RED}DIFF KO${RESET} \xE2\x9D\x8C \n\n"
fi
