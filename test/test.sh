#!/bin/bash

VERBOSE=

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/.."
LOG_FOLDER="$ROOT/test/log"
DATA_FOLDER="$ROOT/test/data"

GREEN="\033[32;01m"
RED="\033[31;01m"
NORMAL="\033[0m"

INVALID_FILES="$(find "$DATA_FOLDER/invalid_asm" -name \*.s)"
VALID_FILES="$(find "$ROOT/ressources" -name \*.s)"

error() {
	echo -e "\n$RED$1$NORMAL"
    tail -n 42 "$2"
    cat "$3"
	exit 1
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
		|| error "$base_f (valid file) failed :/" "$f" "$LOG_FOLDER/$base_f.log"
    diff -y --suppress-common-lines <(hexdump -vC "$(echo "$f" | sed -E 's|(.*)s$|\1cor|')") <(hexdump -vC "$(echo "$f" | sed -E 's|(.*)s$|\1cor|' | sed -E 's|test_asm|ctrl_cor|')") \
		|| error "$base_f (valid file) cor files diff :/" "$f" "$LOG_FOLDER/$base_f.log"
	test $VERBOSE && echo && cat "$f" && cat "$LOG_FOLDER/$base_f.log"
	success "$base_f (valid file) ok!"
done

test "$UNIT_RET" = "0" && success "yay" || exit $UNIT_RET
