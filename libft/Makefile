# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 09:52:36 by alucas-           #+#    #+#              #
#    Updated: 2018/03/15 12:39:23 by mc               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##
## CUSTOM CONFIG
##

# name of the binary to make
PROJECT ?= libft

# file-names of the sources
SRC_NAME = \
  cty/cty.c cty/cty_2.c cty/cty_3.c \
  ds/alloc.c ds/apd.c ds/at.c ds/aver.c ds/back.c ds/begin.c ds/clean.c \
  ds/clr.c ds/cpush.c ds/cput.c ds/ctor.c ds/cusht.c ds/dtor.c ds/emp.c \
  ds/end.c ds/grow.c ds/len.c ds/mpush.c ds/mput.c ds/musht.c ds/npop.c \
  ds/npush.c ds/nput.c ds/nrem.c ds/nsht.c ds/nusht.c ds/pop.c ds/prd.c \
  ds/push.c ds/put.c ds/rem.c ds/sht.c ds/usht.c ds/mdtor.c ds/map.c \
  ds/map_2.c ds/set.c ds/set_2.c \
  ex/ex.c ex/ex_2.c \
  fs/fs.c fs/fs_2.c fs/fs_3.c fs/fs_4.c \
  glob/globux.c glob/glob_match.c glob/glob_climb_tree.c \
  glob/glob_util/glob_list.c glob/glob_util/glob_dir.c \
  glob/glob_util/glob_is_magic.c glob/glob_util/glob_path.c \
  glob/glob_util/glob_show.c glob/glob_util/glob_finder.c \
  glob/glob_util/glob_sanitize.c glob/glob_brace.c \
  hash/hash.c hash/hash_2.c \
  int/len.c int/str.c \
  io/fmt/eval.c io/fmt/fmtd.c io/fmt/fmtm.c io/fmt/fmtpct.c io/fmt/fmts.c \
  io/fmt/fmtxp.c io/fmt/parse.c io/fmt/type.c io/asprintf.c io/dprintf.c \
  io/fprintf.c io/fwrite.c io/printf.c io/snprintf.c io/sprintf.c io/stderr.c \
  io/stdio.c io/stdout.c io/vasprintf.c io/vdprintf.c io/vfprintf.c \
  io/vprintf.c io/vsnprintf.c io/vsprintf.c io/fflush.c \
  lib/atoi.c lib/clean.c lib/dtor.c lib/getenv.c lib/itoa.c lib/join.c \
  lib/error.c lib/wctomb.c \
  math/imax.c math/imin.c math/m4.c math/m4_mul.c math/m4_rot.c \
  math/m4_trans.c math/pow.c math/pow2_next.c math/umax.c math/umin.c \
  math/v3.c math/v3_2.c math/eq.c math/eq_2.c \
  mem/alloc.c \
  str/bzero.c str/memccpy.c str/memchr.c str/memcmp.c str/memcpy.c \
  str/memdup.c str/memmove.c str/memrcpy.c str/memset.c str/stpcpy.c \
  str/strbstr.c str/strcat.c str/strchr.c str/strcmp.c str/strcpy.c \
  str/strcspn.c str/strdup.c str/strestr.c str/strlcat.c str/strlcpy.c \
  str/strlen.c str/strmchr.c str/strncat.c str/strnchr.c str/strncmp.c \
  str/strncpy.c str/strndup.c str/strnlen.c str/strnstr.c str/strrchr.c \
  str/strscpy.c str/strspn.c str/strstr.c \
  getopt.c ft_print_memory.c mtoi.c npow.c\
  sort/ft_shellsort.c str/ft_memalloc.c str/ft_memdel.c io/get_next_line.c \
  hsh/ft_hdel.c hsh/ft_hdelone.c hsh/ft_hfind.c hsh/ft_hget.c \
  hsh/ft_hiter.c hsh/ft_hnew.c hsh/ft_hset.c \
  arr/ft_arrdel.c arr/ft_arrfind.c arr/ft_arrmult.c arr/ft_arrpush.c arr/ft_arrswap.c \
  arr/ft_arrdup.c arr/ft_arrget.c arr/ft_arrnew.c arr/ft_arrslice.c \
  arr/ft_arrequ.c arr/ft_arrjoin.c arr/ft_arrpop.c arr/ft_arrsort.c

# folder-names of the sources
SRC_PATH = src

# folder-names containing headers files
INC_PATH = include

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
OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))
DEP = $(OBJ:%.o=%.d)

# includes
INC = $(addprefix -I, $(INC_PATH))

# specify flags for commands used in the following rules
RM =		rm -f
RMDIR =		rmdir
MKDIR =		mkdir -p
CC =		clang
MAKE ?=		make -j$(shell nproc 2>/dev/null || echo 4)

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

# add define for os/arch
ifeq ($(OS), Windows_NT)
  CCFLAGS += -D WIN32
  ifeq ($(PROCESSOR_ARCHITECTURE), AMD64)
    CCFLAGS += -D AMD64
  else ifeq ($(PROCESSOR_ARCHITECTURE), x86)
    CCFLAGS += -D IA32
  endif
else
  UNAME_S = $(shell uname -s)
  ifeq ($(UNAME_S), Linux)
    CCFLAGS += -D LINUX
  else ifeq ($(UNAME_S), Darwin)
    CCFLAGS += -D OSX
  endif
  UNAME_P = $(shell uname -p)
  ifeq ($(UNAME_P), unknown)
    UNAME_P = $(shell uname -m)
  endif
  ifeq ($(UNAME_P), x86_64)
    CCFLAGS += -D AMD64
  else ifneq ($(filter %86, $(UNAME_P)), )
    CCFLAGS += -D IA32
  else ifneq ($(filter arm%, $(UNAME_P)), )
    CCFLAGS += -D ARM
  endif
endif


##
## PUBLIC RULES
##

# release build
all:
	@$(PRINTF) "%-20s" "$(PROJECT).a: lib"
	+$(MAKE) $(PROJECT).a "CFLAGS = $(RCFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"
	@$(PRINTF) "$(EVIL)$(TODO_B)$(TODO_A)$(GREEN)✔$(BASIC)\n"

# build for gdb/valgrind debugging
dev:
	@$(PRINTF) "%-20s" "$(PROJECT).dev: exe"
	+$(MAKE) $(PROJECT).dev.a "PROJECT = $(PROJECT).dev" "CFLAGS = $(DCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/dev"
	@$(PRINTF) "$(EVIL)$(TODO_B)$(TODO_A)$(GREEN)✔$(BASIC)\n"

# build for runtime debugging (fsanitize)
san:
	@$(PRINTF) "%-20s" "$(PROJECT).san: exe"
	+$(MAKE) $(PROJECT).san.a "PROJECT = $(PROJECT).san" "CFLAGS = $(SCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/san"
	@$(PRINTF) "$(EVIL)$(TODO_B)$(TODO_A)$(GREEN)✔$(BASIC)\n"

# masochist build
mecry:
	@$(PRINTF) "%-20s" "$(PROJECT).a: gg"
	+$(MAKE) $(PROJECT).a "CFLAGS = $(WWFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"
	@$(PRINTF) "$(EVIL)$(TODO_B)$(TODO_A)$(GREEN)✔$(BASIC)\n"

# remove all generated .o and .d
clean:
	$(RM) $(OBJ) $(DEP)
	$(RM) $(OBJ:$(OBJ_DIR)/rel%=$(OBJ_DIR)/dev%) $(DEP:$(OBJ_DIR)/rel%=$(OBJ_DIR)/dev%)
	$(RM) $(OBJ:$(OBJ_DIR)/rel%=$(OBJ_DIR)/san%) $(DEP:$(OBJ_DIR)/rel%=$(OBJ_DIR)/san%)
	test -d $(OBJ_DIR) && find $(OBJ_DIR) -name '*.[od]' | xargs $(RM) || true
	@$(PRINTF) "%-20s$(GREEN)✔$(BASIC)\n" "$(PROJECT): $@"

# remove the generated binary, and all .o and .d
fclean: clean
	test -d $(OBJ_DIR) && find $(OBJ_DIR) -type d | sort -r | xargs $(RMDIR) || true
	$(RM) $(PROJECT){,.san,.dev}.a
	@$(PRINTF) "%-20s$(GREEN)✔$(BASIC)\n" "$(PROJECT): $@"

# some people like it real clean
mrproper:
	$(RM) -r $(OBJ_DIR)
	+$(MAKE) fclean

# clean build and recompile
re: fclean all

# run tests on project
test: all
	@$(PRINTF) "All tests passed!"

# check coding-style
norme:
	norminette $(INC_PATH) $(SRC_PATH)


##
## PRIVATE RULES
##

# create binary (link)
$(PROJECT).a: $(OBJ)
	@$(PRINTF) "$(EVIL)$(TODO_B)$(TODO_A)$@"
	ar -rc $(PROJECT).a $(OBJ)
	ranlib $(PROJECT).a

# create object files (compile)
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	@$(PRINTF) "$(EVIL)$(TODO_B)$(TODO_A)$<"
	$(CC) $(CFLAGS) $(INC) -MMD -MP -c $< -o $@

# create directory for compilation sub-products
$(OBJ_PATH):
	mkdir -p $(dir $(OBJ))

# read dependencies list generated by -MMD flag
-include $(DEP)

# just to avoid conflicts between rules and files/folders names
.PHONY: all, dev, san, mecry, $(PROJECT).a, clean, fclean, mrproper, re, test, norme
