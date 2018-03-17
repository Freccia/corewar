#!/bin/bash

# VERBOSE=zd

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/.."
LOG_FOLDER="$ROOT/test/log"
DATA_FOLDER="$ROOT/test/ressources"

GREEN="\033[32;01m"
RED="\033[31;01m"
NORMAL="\033[0m"

INVALID_FILES="$(find "$DATA_FOLDER/invalid_asm" -name \*.s)"
VALID_FILES="$(find "$ROOT/ressources" -name \*.s)"

error() {
	echo -e "\n$RED$1$NORMAL"
    test $VERBOSE && cat "$2" # asm file
    cat "$3" # log file
    test "$4" && echo "$4" # diff
	test $VERBOSE || exit 1
}

success() {
	echo -e "$GREEN$1$NORMAL"
}

# functional tests
mkdir -p "$LOG_FOLDER"

for f in $INVALID_FILES; do
	base_f="$(basename "$f")"
	"$ROOT/asm" "$f" &> "$LOG_FOLDER/$base_f.log" && error "$base_f (invalid file) succeed :/" "$f" #TODO: catch asm crash :o
	test $VERBOSE && echo && cat "$f" && cat "$LOG_FOLDER/$base_f.log"
	success "$base_f (invalid file) ok!"
done

for f in $VALID_FILES; do
	base_f="$(basename "$f")"
	"$ROOT/asm" "$f" &> "$LOG_FOLDER/$base_f.log" \
		|| error "$base_f (valid file) failed :/" \
				 "$f" \
				 "$LOG_FOLDER/$base_f.log"

	test_file="$(echo "$f" | sed -E 's|(.*)s$|\1cor|')"
	ctrl_file="$DATA_FOLDER/ctrl_cor/$(basename "$f" | sed -E 's|(.*)s$|\1cor|')"
    diff "$test_file" "$ctrl_file" >/dev/null 2>&1 \
		|| error "$base_f (valid file) cor files diff :/" \
				 "$f" \
				 "$LOG_FOLDER/$base_f.log" \
				 "$(diff -y <(hexdump -vC "$test_file") <(hexdump -vC "$ctrl_file"))"

	success "$base_f (valid file) ok!"
done

success "yay"
