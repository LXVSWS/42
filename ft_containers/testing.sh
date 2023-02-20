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
printf "${WHITE}FT_CONTAINERS TESTER |\n_____________________|\n\n${YELLOW}COMPILING...${RESET}"
clean=$(make fclean)
make=$(make)
std
test=$(make test)
ft
clear
printf "${WHITE}FT_CONTAINERS TESTER |\n_____________________|\n\n${GREEN}COMPILATION OK \xE2\x9C\x85${RESET}\n\n"
printf "${WHITE}• VECTOR TESTS •${RESET}\n\n${YELLOW}CONSTRUCTOR${RESET} | "
diff=$(diff <(./ft_containers 0) <(./std_containers 0))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 1
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 1
sleep 1
printf "\n${YELLOW}CONSTRUCTOR (ITERATORS)${RESET} | "
diff=$(diff <(./ft_containers 2) <(./std_containers 2))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 3
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 3
sleep 1
printf "\n${YELLOW}COPY CONSTRUCTOR${RESET} | "
diff=$(diff <(./ft_containers 4) <(./std_containers 4))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 5
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 5
sleep 1
printf "\n${YELLOW}OPERATOR= OVERLOADING${RESET} | "
diff=$(diff <(./ft_containers 6) <(./std_containers 6))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 7
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 7
sleep 1
printf "\n${YELLOW}SIZE${RESET} | "
diff=$(diff <(./ft_containers 8) <(./std_containers 8))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 9
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 9
sleep 1
printf "\n${YELLOW}MAX_SIZE${RESET} | "
diff=$(diff <(./ft_containers a) <(./std_containers a))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers b
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers b
sleep 1
printf "\n${YELLOW}RESIZE${RESET} | "
diff=$(diff <(./ft_containers c) <(./std_containers c))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers d
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers d
sleep 1
printf "\n${YELLOW}CAPACITY${RESET} | "
diff=$(diff <(./ft_containers e) <(./std_containers e))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers f
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers f
sleep 1
printf "\n${YELLOW}EMPTY${RESET} | "
diff=$(diff <(./ft_containers g) <(./std_containers g))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers h
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers h
sleep 1
printf "\n${YELLOW}RESERVE${RESET} | "
diff=$(diff <(./ft_containers i) <(./std_containers i))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers j
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers j
sleep 1
printf "\n${YELLOW}OPERATOR[] OVERLOADING${RESET} | "
diff=$(diff <(./ft_containers k) <(./std_containers k))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers l
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers l
sleep 1
printf "\n${YELLOW}AT${RESET} | "
diff=$(diff <(./ft_containers m) <(./std_containers m))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers n
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers n
sleep 1
printf "\n${YELLOW}FRONT${RESET} | "
diff=$(diff <(./ft_containers o) <(./std_containers o))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers p
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers p
sleep 1
printf "\n${YELLOW}BACK${RESET} | "
diff=$(diff <(./ft_containers q) <(./std_containers q))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers r
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers r
sleep 1
printf "\n${YELLOW}DATA${RESET} | "
diff=$(diff <(./ft_containers s) <(./std_containers s))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers t
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers t
sleep 1
printf "\n${YELLOW}ASSIGN (ITERATORS)${RESET} | "
diff=$(diff <(./ft_containers u) <(./std_containers u))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers v
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers v
sleep 1
printf "\n${YELLOW}ASSIGN${RESET} | "
diff=$(diff <(./ft_containers w) <(./std_containers w))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers x
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers x
sleep 1
printf "\n${YELLOW}PUSH_BACK${RESET} | "
diff=$(diff <(./ft_containers y) <(./std_containers y))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers z
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers z
sleep 1
