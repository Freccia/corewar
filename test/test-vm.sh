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

success() {
	echo -e "$GREEN$1$NORMAL"
}

test-vm() {
    cycles="$1"
    core_file="$2"

    ctrl_file="$DUMP_FOLDER"/"$(basename $core_file)"_"$cycles"-cycles.dump

    # "$ROOT/ressources/bin/corewar" -d "$cycles" "$core_file" "$core_file" > "$ctrl_file"

    # -y --suppress-common-lines
    diff -y --width 400 --suppress-common-lines "$ctrl_file" <("$ROOT/corewar" -d "$cycles" "$core_file" "$core_file" 2>/dev/null) \
        || error "corewar dump failed: with args: -d $cycles $core_file $core_file"
    #TODO: not sure which files to send here?
}

# functional tests
mkdir -p "$LOG_FOLDER"

for f in $COR_FILES; do
    for i in $(seq 10 10 250); do
        test-vm "$i" "$f"
    done
done
success yay
