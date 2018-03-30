#!/bin/bash

VERBOSE=

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/.."
LOG_FOLDER="$ROOT/test/log"
DATA_FOLDER="$ROOT/test/ressources"
DUMP_FOLDER="$ROOT/test/ressources/cor_dump"

COR_FILES="$(find "$ROOT/test/ressources/ctrl_cor" -name \*.cor)"

GREEN="\033[32;01m"
RED="\033[31;01m"
NORMAL="\033[0m"

error() {
	echo -e "\n$RED$1$NORMAL"
	exit 1
}

error1() {
    echo -e "\n$RED$1$NORMAL"
}

success() {
	echo -e "$GREEN$1$NORMAL"
}

test-vm() {
    cycles="$1"
    core_file="$2"

    ctrl_file="$DUMP_FOLDER"/"$(basename $core_file)"_"$cycles"-cycles.dump

    # to generate cor dumps:
    # "$ROOT/ressources/bin/corewar" -d "$cycles" "$core_file" "$core_file" > "$ctrl_file"

    if test -e "$ctrl_file"; then
        diff -y --width 400 --suppress-common-lines <(grep -vE 'Introducing|Player' "$ctrl_file") <("$ROOT/corewar" -d "$cycles" "$core_file" "$core_file" | grep -vE 'Introducing|Player') \
            #|| error "corewar dump failed: with args: -d $cycles $core_file $core_file"
        if [ $? -ne 0 ]; then
            error1 "corewar dump failed: with args: -d $cycles $core_file $core_file"
        else
            success "$core_file $cycles cycles ok!"
        fi
    fi
}

# functional tests
mkdir -p "$LOG_FOLDER"

if test -z "$1"; then
    for f in $COR_FILES; do
        for i in $(seq 10 10 250); do
            test-vm "$i" "$f"
        done
    done
    success yay
else
    for i in $(seq 10 10 250); do
        test-vm "$i" "$1"
    done
fi
