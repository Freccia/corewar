# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 09:52:36 by alucas-           #+#    #+#              #
#    Updated: 2018/03/29 11:22:00 by lfabbro          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##
## CUSTOM CONFIG
##

# name of the binaries to make
PROJECTA ?= asm
PROJECTB ?= corewar

# file-names of the sources
COMMON_SRC = \
	op.c \
	utils.c
SRCA_NAME = \
	$(COMMON_SRC) \
	asm/asm_main.c \
	asm/init_data.c \
	asm/error.c \
	asm/encoder/asm_encoder.c \
	asm/encoder/write_cor.c \
	asm/lexer/asm_lexer.c \
	asm/lexer/read_header.c \
	asm/lexer/read_instruction.c \
	asm/lexer/read_comment.c \
	asm/lexer/check_arg_len.c \
	asm/parser/asm_parser.c \
	asm/parser/parse_args.c
SRCB_NAME = \
	$(COMMON_SRC) \
	vm/gui/exit.c vm/gui/init.c vm/gui/keys.c vm/gui/ui.c \
	vm/init.c \
	vm/eval.c vm/instr/add.c vm/instr/aff.c vm/instr/and.c vm/instr/fork.c \
	vm/instr/ld.c vm/instr/ldi.c vm/instr/lfork.c vm/instr/live.c vm/instr/lld.c \
	vm/instr/lldi.c vm/instr/or.c vm/instr/st.c vm/instr/sti.c vm/instr/sub.c \
	vm/instr/xor.c vm/instr/zjmp.c vm/instr/gtmd.c\
	vm/main.c \
	vm/opt.c \
	vm/player.c \
	vm/proc.c \
	vm/read.c \
	vm/run.c \
  vm/write.c

# folder-names of the sources
SRC_PATH = src

# where are your tests?
TEST_DIR =	test

# vendor (mostly libft, right?)
LFT_DIR = libft
LFT_INC_PATH = $(LFT_DIR)/include
LFT_LDFLAGS = -L $(LFT_DIR)
LFT_LDLIBS ?= -lft
LFT ?= libft.a

# folder-names containing headers files
INC_PATH = $(LFT_INC_PATH) include

# extra libraries needed for linking
LDLIBS = $(LFT_LDLIBS) -lncurses # -lm

# linking flags
LDFLAGS = $(LFT_LDFLAGS)

# compilation flags
CPPFLAGS =


##
## GLOBAL VARIABLES
##

# compilation/linking flags for the differents public rules
WFLAGS = -Wextra -Wall  # warnings
RCFLAGS = $(WFLAGS) -Werror -O2  # release
DCFLAGS = $(WFLAGS) -g3 -DDEBUG  # debug
SCFLAGS = $(DCFLAGS) -fsanitize=address,undefined -ferror-limit=5  # sanitize
WWFLAGS = $(WFLAGS) -Wpedantic -Wshadow -Wconversion -Wcast-align \
  -Wstrict-prototypes -Wmissing-prototypes -Wunreachable-code -Winit-self \
  -Wmissing-declarations -Wfloat-equal -Wbad-function-cast -Wundef \
  -Waggregate-return -Wstrict-overflow=5 -Wold-style-definition -Wpadded \
  -Wredundant-decls  # moar warnings

# folder used to store all compilations sub-products (.o and .d mostly)
OBJ_DIR ?= obj
OBJ_PATH ?= $(OBJ_DIR)/rel
OBJA = $(addprefix $(OBJ_PATH)/, $(SRCA_NAME:.c=.o))
OBJB = $(addprefix $(OBJ_PATH)/, $(SRCB_NAME:.c=.o))
DEP = $(OBJA:%.o=%.d) $(OBJB:%.o=%.d)

# includes
INC = $(addprefix -I, $(INC_PATH))

# specify flags for commands used in the following rules
RM =		rm -f
RMDIR =		rmdir
MKDIR =		mkdir -p
CC =		clang
MAKE ?=		make -j$(shell nproc 2>/dev/null || echo 4)
SUB_MAKE =	make -C

# default to "pretty" Makefile, but you can run ´VERBOSE=t make´
ifndef VERBOSE
 ifndef TRAVIS
.SILENT:
 endif
endif
PRINTF = test $(VERBOSE)$(TRAVIS) || printf

# some colors for pretty printing
WHITE =		\033[37m
RED =		\033[31m
GREEN =		\033[32m
YELLOW =	\033[33m
BLUE =		\033[34m
BASIC =		\033[0m
TODO_A =	\033[0K  #TODO
TODO_B =	\033[17C #TODO
EVIL =		\r

##
## PUBLIC RULES
##

# release build
all:
	+$(SUB_MAKE) $(LFT_DIR)
	@$(PRINTF) "%-20s" "$(PROJECTA): exe"
	+$(MAKE) $(PROJECTA) "CFLAGS = $(RCFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"
	@$(PRINTF) "$(EVIL)$(TODO_B)$(TODO_A)$(GREEN)✔$(BASIC)\n"
	@$(PRINTF) "%-20s" "$(PROJECTB): exe"
	+$(MAKE) $(PROJECTB) "CFLAGS = $(RCFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"
	@$(PRINTF) "$(EVIL)$(TODO_B)$(TODO_A)$(GREEN)✔$(BASIC)\n"

# build for gdb/valgrind debugging
dev:
	+$(SUB_MAKE) $(LFT_DIR) dev
	@$(PRINTF) "%-20s" "$(PROJECTA).dev: exe"
	+$(MAKE) $(PROJECTA).dev "PROJECTA = $(PROJECTA).dev" "CFLAGS = $(DCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/dev" "LFT = libft.dev.a" "LFT_LDLIBS = -lft.dev"
	@$(PRINTF) "$(EVIL)$(TODO_B)$(TODO_A)$(GREEN)✔$(BASIC)\n"
	@$(PRINTF) "%-20s" "$(PROJECTB).dev: exe"
	+$(MAKE) $(PROJECTB).dev "PROJECTB = $(PROJECTB).dev" "CFLAGS = $(DCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/dev" "LFT = libft.dev.a" "LFT_LDLIBS = -lft.dev"
	@$(PRINTF) "$(EVIL)$(TODO_B)$(TODO_A)$(GREEN)✔$(BASIC)\n"

# build for runtime debugging (fsanitize)
san:
	+$(SUB_MAKE) $(LFT_DIR) san
	@$(PRINTF) "%-20s" "$(PROJECTA).san: exe"
	+$(MAKE) $(PROJECTA).san "PROJECTA = $(PROJECTA).san" "CFLAGS = $(SCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/san" "LFT = libft.san.a" "LFT_LDLIBS = -lft.san"
	@$(PRINTF) "$(EVIL)$(TODO_B)$(TODO_A)$(GREEN)✔$(BASIC)\n"
	@$(PRINTF) "%-20s" "$(PROJECTB).san: exe"
	+$(MAKE) $(PROJECTB).san "PROJECTB = $(PROJECTB).san" "CFLAGS = $(SCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/san" "LFT = libft.san.a" "LFT_LDLIBS = -lft.san"
	@$(PRINTF) "$(EVIL)$(TODO_B)$(TODO_A)$(GREEN)✔$(BASIC)\n"

# masochist build
mecry:
	+$(SUB_MAKE) $(LFT_DIR) mecry
	@$(PRINTF) "%-20s" "$(PROJECTA): gg"
	+$(MAKE) $(PROJECTA) "CFLAGS = $(WWFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"
	@$(PRINTF) "$(EVIL)$(TODO_B)$(TODO_A)$(GREEN)✔$(BASIC)\n"
	@$(PRINTF) "%-20s" "$(PROJECTB): gg"
	+$(MAKE) $(PROJECTB) "CFLAGS = $(WWFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"
	@$(PRINTF) "$(EVIL)$(TODO_B)$(TODO_A)$(GREEN)✔$(BASIC)\n"

# remove all generated .o and .d
clean:
	$(RM) $(OBJ) $(DEP)
	$(RM) $(OBJ:$(OBJ_DIR)/rel%=$(OBJ_DIR)/dev%) $(DEP:$(OBJ_DIR)/rel%=$(OBJ_DIR)/dev%)
	$(RM) $(OBJ:$(OBJ_DIR)/rel%=$(OBJ_DIR)/san%) $(DEP:$(OBJ_DIR)/rel%=$(OBJ_DIR)/san%)
	test -d $(OBJ_DIR) && find $(OBJ_DIR) -name '*.[od]' | xargs $(RM) || true
	@$(PRINTF) "%-20s$(GREEN)✔$(BASIC)\n" "$(PROJECTB): $@"

# remove the generated binary, and all .o and .d
fclean: clean
	test -d $(OBJ_DIR) && find $(OBJ_DIR) -type d | sort -r | xargs $(RMDIR) || true
	$(RM) {$(PROJECTA),$(PROJECTB)}{,.san,.dev}
	@$(PRINTF) "%-20s$(GREEN)✔$(BASIC)\n" "$(PROJECTB): $@"

# some people like it real clean
mrproper:
	+$(SUB_MAKE) $(LFT_DIR) fclean
	$(RM) -r $(OBJ_DIR)
	+$(MAKE) fclean

# clean build and recompile
re: fclean all

# run tests on project
test: all
	$(TEST_DIR)/test-asm.sh || true
	$(TEST_DIR)/test-vm.sh || true

#TODO
# # run tests on project (debug mode)
# testdev: dev
# 	$(TEST_DIR)/test-asm.sh $(PROJECTA) || true
# 	$(TEST_DIR)/test-vm.sh $(PROJECTB) || true

# # run tests on project (sanitize mode)
# testsan: san
# 	$(TEST_DIR)/test-asm.sh $(PROJECTA) || true
# 	$(TEST_DIR)/test-vm.sh $(PROJECTB) || true

# check coding-style
norme:
	+$(SUB_MAKE) $(LFT_DIR) norme
	norminette $(INC_PATH) $(SRC_PATH)


##
## PRIVATE RULES
##

# create binary A (link)
$(PROJECTA): $(LFT_DIR)/$(LFT) $(OBJA)
	@$(PRINTF) "$(EVIL)$(TODO_B)$(TODO_A)$@"
	$(CC) $(CFLAGS) $(INC) $(LDFLAGS) $(OBJA) $(LDLIBS) -o $@

# create binary B (link)
$(PROJECTB): $(LFT_DIR)/$(LFT) $(OBJB)
	@$(PRINTF) "$(EVIL)$(TODO_B)$(TODO_A)$@"
	$(CC) $(CFLAGS) $(INC) $(LDFLAGS) $(OBJB) $(LDLIBS) -o $@

# create object files (compile)
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	@$(PRINTF) "$(EVIL)$(TODO_B)$(TODO_A)$<"
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) -MMD -MP -c $< -o $@

# create directory for compilation sub-products
$(OBJ_PATH):
	$(MKDIR) $(dir $(OBJA) $(OBJB))

# read dependencies list generated by -MMD flag
-include $(DEP)

# just to avoid conflicts between rules and files/folders names
.PHONY: all, dev, san, mecry, $(PROJECTA), $(PROJECTB), clean, fclean, mrproper, re, test, norme
