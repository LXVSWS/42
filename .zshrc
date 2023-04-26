alias save="git add . && git commit -m 'save' && git push"
alias gccc="gcc -Wall -Wextra -Werror -g"
alias czsh="cd && rm .zshrc && cp Desktop/42/.zshrc ."
alias setcode="cd ~/Library/Application\ Support/Code/User/ && rm settings.json && cp ~/Desktop/42/settings.json ."

export ZSH="$HOME/.oh-my-zsh"

ZSH_THEME="eastwood"

COMPLETION_WAITING_DOTS="true"
COMPLETION_WAITING_DOTS="%F{red}...%f"

plugins=(git)

source $ZSH/oh-my-zsh.sh
