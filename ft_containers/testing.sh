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
printf "${WHITE}FT_CONTAINERS TESTER |\n_____________________|\n\n${GREEN}COMPILATION OK \xE2\x9C\x85${RESET}\n"
printf "\n${WHITE}• VECTOR TESTS •${RESET}\n\n${YELLOW}EMPTY CONSTRUCTOR${RESET} | "
diff=$(diff <(./ft_containers !) <(./std_containers !))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers $
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers $
sleep 1
printf "\n${YELLOW}CONSTRUCTOR${RESET} | "
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
printf "\n${YELLOW}POP_BACK${RESET} | "
diff=$(diff <(./ft_containers 00) <(./std_containers 00))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 01
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 01
sleep 1
printf "\n${YELLOW}INSERT${RESET} | "
diff=$(diff <(./ft_containers 02) <(./std_containers 02))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 03
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 03
sleep 1
printf "\n${YELLOW}INSERT (FILL)${RESET} | "
diff=$(diff <(./ft_containers 04) <(./std_containers 04))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 05
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 05
sleep 1
printf "\n${YELLOW}INSERT (ITERATORS)${RESET} | "
diff=$(diff <(./ft_containers 06) <(./std_containers 06))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 07
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 07
sleep 1
printf "\n${YELLOW}ERASE${RESET} | "
diff=$(diff <(./ft_containers 08) <(./std_containers 08))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 09
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 09
sleep 1
printf "\n${YELLOW}ERASE (RANGE)${RESET} | "
diff=$(diff <(./ft_containers 10) <(./std_containers 10))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 11
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 11
sleep 1
printf "\n${YELLOW}SWAP (MEMBER & OVERLOADED)${RESET} | "
diff=$(diff <(./ft_containers 12) <(./std_containers 12))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 13
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 13
sleep 1
printf "\n${YELLOW}CLEAR${RESET} | "
diff=$(diff <(./ft_containers 14) <(./std_containers 14))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 15
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 15
sleep 1
printf "\n${YELLOW}COMPARISON OPERATORS${RESET} | "
diff=$(diff <(./ft_containers 16) <(./std_containers 16))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 17
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 17
sleep 1
printf "\n${YELLOW}ITERATORS & REVERSE ITERATORS${RESET} | "
diff=$(diff <(./ft_containers 18) <(./std_containers 18))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 19
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 19
sleep 1
printf "\n${WHITE}• MAP TESTS •${RESET}\n\n${YELLOW}CONSTRUCTOR${RESET} | "
diff=$(diff <(./ft_containers 20) <(./std_containers 20))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 21
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 21
sleep 1
printf "\n${YELLOW}CONSTRUCTOR (RANGE)${RESET} | "
diff=$(diff <(./ft_containers 22) <(./std_containers 22))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 23
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 23
sleep 1
printf "\n${YELLOW}COPY CONSTRUCTOR${RESET} | "
diff=$(diff <(./ft_containers 24) <(./std_containers 24))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 25
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 25
sleep 1
printf "\n${YELLOW}OPERATOR= OVERLOADING${RESET} | "
diff=$(diff <(./ft_containers 26) <(./std_containers 26))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 27
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 27
sleep 1
printf "\n${YELLOW}EMPTY${RESET} | "
diff=$(diff <(./ft_containers 28) <(./std_containers 28))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 29
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 29
sleep 1
printf "\n${YELLOW}SIZE${RESET} | "
diff=$(diff <(./ft_containers 30) <(./std_containers 30))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 31
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 31
sleep 1
printf "\n${YELLOW}OPERATOR[] OVERLOADING${RESET} | "
diff=$(diff <(./ft_containers 32) <(./std_containers 32))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 33
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 33
sleep 1
printf "\n${YELLOW}AT${RESET} | "
diff=$(diff <(./ft_containers 34) <(./std_containers 34))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 35
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 35
sleep 1
printf "\n${YELLOW}INSERT${RESET} | "
diff=$(diff <(./ft_containers 36) <(./std_containers 36))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 37
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 37
sleep 1
printf "\n${YELLOW}INSERT (RANGE)${RESET} | "
diff=$(diff <(./ft_containers 38) <(./std_containers 38))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 39
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 39
sleep 1
printf "\n${YELLOW}ERASE${RESET} | "
diff=$(diff <(./ft_containers 40) <(./std_containers 40))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 41
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 41
sleep 1
printf "\n${YELLOW}ERASE (KEY)${RESET} | "
diff=$(diff <(./ft_containers 42) <(./std_containers 42))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 43
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 43
sleep 1
printf "\n${YELLOW}ERASE (RANGE)${RESET} | "
diff=$(diff <(./ft_containers 44) <(./std_containers 44))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 45
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 45
sleep 1
printf "\n${YELLOW}SWAP (MEMBER & OVERLOADED)${RESET} | "
diff=$(diff <(./ft_containers 46) <(./std_containers 46))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 47
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 47
sleep 1
printf "\n${YELLOW}CLEAR${RESET} | "
diff=$(diff <(./ft_containers 48) <(./std_containers 48))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 49
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 49
sleep 1
printf "\n${YELLOW}FIND${RESET} | "
diff=$(diff <(./ft_containers 50) <(./std_containers 50))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 51
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 51
sleep 1
printf "\n${YELLOW}COUNT${RESET} | "
diff=$(diff <(./ft_containers 52) <(./std_containers 52))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 53
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 53
sleep 1
printf "\n${YELLOW}LOWER & UPPER BOUND${RESET} | "
diff=$(diff <(./ft_containers 54) <(./std_containers 54))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 55
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 55
sleep 1
printf "\n${YELLOW}EQUAL RANGE${RESET} | "
diff=$(diff <(./ft_containers 56) <(./std_containers 56))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 57
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 57
sleep 1
printf "\n${YELLOW}COMPARISON OPERATORS${RESET} | "
diff=$(diff <(./ft_containers 58) <(./std_containers 58))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 59
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 59
sleep 1
printf "\n${YELLOW}ITERATORS & REVERSE ITERATORS${RESET} | "
diff=$(diff <(./ft_containers 60) <(./std_containers 60))
if [ -z "$diff" ]
then
printf "${GREEN}OK${RESET} \xE2\x9C\x85"
else
printf "${RED}KO${RESET} \xE2\x9D\x8C"
fi
printf "\n${CYAN}FT  EXEC TIME : ${RESET}"
./ft_containers 61
printf "${BLUE}STD EXEC TIME : ${RESET}"
./std_containers 61
printf "\n \xE2\x9C\x85 ${GREEN}SUCCESS${RESET} \xE2\x9C\x85 \n\n"
