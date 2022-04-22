alias save="git add . && git commit -m 'save' && git push"
alias gccc="gcc -Wall -Wextra -Werror -g"
alias czsh="cd && rm .zshrc && cp Desktop/42/.zshrc ."
alias setcode="cd ~/Library/Application\ Support/Code/User/ && rm settings.json && cp ~/Desktop/42/settings.json ."

export ZSH="$HOME/.oh-my-zsh"
export PATH=$HOME/.brew/bin:$PATH

# rm -rf $HOME/.brew && gcl --depth=1 https://github.com/Homebrew/brew $HOME/.brew && brew update

ZSH_THEME="eastwood"

COMPLETION_WAITING_DOTS="true"
COMPLETION_WAITING_DOTS="%F{red}...%f"

plugins=(git)

source $ZSH/oh-my-zsh.sh

# ZSH_CUSTOM=/path/to/new-custom-folder
# CASE_SENSITIVE="true"
# HYPHEN_INSENSITIVE="true"
# DISABLE_MAGIC_FUNCTIONS="true"
# DISABLE_LS_COLORS="true"
# DISABLE_AUTO_TITLE="true"
# ENABLE_CORRECTION="true"
# DISABLE_UNTRACKED_FILES_DIRTY="true"
# "mm/dd/yyyy"|"dd.mm.yyyy"|"yyyy-mm-dd"
# HIST_STAMPS="mm/dd/yyyy"
# Standard plugins -> $ZSH/plugins/
# Custom plugins -> $ZSH_CUSTOM/plugins/
# export MANPATH="/usr/local/man:$MANPATH"
# export LANG=en_US.UTF-8
# export ARCHFLAGS="-arch x86_64"
