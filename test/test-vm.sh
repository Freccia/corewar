#!/bin/bash

VERBOSE=

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/.."
LOG_FOLDER="$ROOT/test/log"
DATA_FOLDER="$ROOT/test/ressources"

COR_FILES="$(find "$ROOT/test/ressources/ctrl_cor" -name \*.cor)"

GREEN="\033[32;01m"
RED="\033[31;01m"
NORMAL="\033[0m"

error() {
	echo -e "\n$RED$1$NORMAL"
    tail -n 42 "$2"
    cat "$3"
	exit 1
}

success() {
	echo -e "$GREEN$1$NORMAL"
}

test-vm() {
    cycles="$1"
    core_file="$2"

    # "$ROOT/corewar" -d "$cycles" "$core_file" "$core_file"
    #TODO: not sure which files to send here?
}

# functional tests
mkdir -p "$LOG_FOLDER"

for f in $COR_FILES; do
    for i in {0..64}; do
        test-vm "$i" "$f"
    done
done
