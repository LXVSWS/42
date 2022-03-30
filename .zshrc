alias save="git add . && git commit -m 'save' && git push"
alias gccc="gcc -Wall -Wextra -Werror -g"

export ZSH="$HOME/.oh-my-zsh"

ZSH_THEME="trapd00r"

COMPLETION_WAITING_DOTS="true"
COMPLETION_WAITING_DOTS="%F{yellow}...%f"

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
