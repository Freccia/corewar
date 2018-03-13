# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 09:52:36 by alucas-           #+#    #+#              #
#    Updated: 2018/03/13 21:43:49 by mcanal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECTA ?= asm
PROJECTB ?= corewar
WFLAGS = -Werror -Wextra -Wall
RCFLAGS = $(WFLAGS) -O2
CC = clang

INC_PATH = include src/asm
SRC_PATH = src
OBJ_DIR ?= obj
OBJ_PATH ?= $(OBJ_DIR)/rel
3TH_PATH = .

LIBS = ft
ifneq (,$(findstring dev,$(PROJECT)))
LIB_NAME = $(addsuffix .dev, $(LIBS))
else ifneq (,$(findstring san,$(PROJECT)))
LIB_NAME = $(addsuffix .san, $(LIBS))
else
LIB_NAME = $(LIBS)
endif
3TH_NAME = libft
SRCA_NAME = \
	asm/asm_main.c \
	asm/init_data.c \
	asm/error.c \
	asm/encoder/asm_encoder.c \
	asm/encoder/write_cor.c \
	asm/lexer/asm_lexer.c \
	asm/lexer/read_header.c \
	asm/lexer/read_instruction.c \
	asm/parser/asm_parser.c \
	asm/parser/parse_args.c \

SRCB_NAME = \
	vm/vm.c

3TH = $(addprefix $(3TH_PATH)/, $(3TH_NAME))
OBJA = $(addprefix $(OBJ_PATH)/, $(SRCA_NAME:.c=.o))
OBJB = $(addprefix $(OBJ_PATH)/, $(SRCB_NAME:.c=.o))
LNK = $(addprefix -L, $(3TH))
INC = $(addprefix -I, $(INC_PATH) $(addsuffix /include, $(3TH)))
LIB = $(addprefix -l, $(LIB_NAME))
DEP = $(OBJ:%.o=%.d)

PRINTF=test $(VERBOSE)$(TRAVIS) || printf
ifneq (,$(findstring dev,$(PROJECT)))
3DE = $(shell echo "$(3TH_NAME)" | sed -E "s|([\.a-zA-Z]+)|$(3TH_PATH)/\1/\1.dev.a|g")
else ifneq (,$(findstring san,$(PROJECT)))
3DE = $(shell echo "$(3TH_NAME)" | sed -E "s|([\.a-zA-Z]+)|$(3TH_PATH)/\1/\1.san.a|g")
else
3DE = $(shell echo "$(3TH_NAME)" | sed -E "s|([\.a-zA-Z]+)|$(3TH_PATH)/\1/\1.a|g")
endif

all:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) &&) true
endif
	@$(PRINTF) "%-20s" "$(PROJECTA): exe"
	+$(MAKE) -j4 $(PROJECTA) "CFLAGS = $(RCFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"
	@$(PRINTF) "\r\x1b[20C\x1b[0K\x1b[32m✔\x1b[0m\n"
	@$(PRINTF) "%-20s" "$(PROJECTB): exe"
	+$(MAKE) -j4 $(PROJECTB) "CFLAGS = $(RCFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"
	@$(PRINTF) "\r\x1b[20C\x1b[0K\x1b[32m✔\x1b[0m\n"

dev:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) dev &&) true
endif
	@$(PRINTF) "%-20s" "$(PROJECTA).dev: exe"
	+$(MAKE) -j4 $(PROJECTA).dev "PROJECTA = $(PROJECTA).dev" "CFLAGS = $(DCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/dev"
	@$(PRINTF) "\r\x1b[20C\x1b[0K\x1b[32m✔\x1b[0m\n"
	@$(PRINTF) "%-20s" "$(PROJECTB).dev: exe"
	+$(MAKE) -j4 $(PROJECTB).dev "PROJECTB = $(PROJECTB).dev" "CFLAGS = $(DCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/dev"
	@$(PRINTF) "\r\x1b[20C\x1b[0K\x1b[32m✔\x1b[0m\n"

san:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) san &&) true
endif
	@$(PRINTF) "%-20s" "$(PROJECTA).san: exe"
	+$(MAKE) -j4 $(PROJECTA).san "PROJECTA = $(PROJECTA).san" "CFLAGS = $(SCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/san" "CC = clang"
	@$(PRINTF) "\r\x1b[20C\x1b[0K\x1b[32m✔\x1b[0m\n"
	@$(PRINTF) "%-20s" "$(PROJECTB).san: exe"
	+$(MAKE) -j4 $(PROJECTB).san "PROJECTB = $(PROJECTB).san" "CFLAGS = $(SCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/san" "CC = clang"
	@$(PRINTF) "\r\x1b[20C\x1b[0K\x1b[32m✔\x1b[0m\n"

$(PROJECTA): $(3DE) $(OBJA)
	@$(PRINTF) "\r\x1b[20C\x1b[0K$@"
	$(CC) $(CFLAGS) $(INC) $(LNK) $(OBJA) $(LIB) -o $(PROJECTA)

$(PROJECTB): $(3DE) $(OBJB)
	@$(PRINTF) "\r\x1b[20C\x1b[0K$@"
	$(CC) $(CFLAGS) $(INC) $(LNK) $(OBJB) $(LIB) -o $(PROJECTB)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	@$(PRINTF) "\r\x1b[20C\x1b[0K$<"
	$(CC) $(CFLAGS) $(INC) -MMD -MP -c $< -o $@

$(OBJ_PATH):
	mkdir -p $(dir $(OBJA) $(OBJB))

clean:
	rm -rf $(OBJ_DIR)
	@$(PRINTF) "%-20s\033[32m✔\033[0m\n" "$(PROJECTB): $@"

fclean: clean
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) fclean &&) true
endif
	rm -f $(PROJECTA){,.san,.dev}
	rm -f $(PROJECTB){,.san,.dev}
	@$(PRINTF) "%-20s\033[32m✔\033[0m\n" "$(PROJECTB): $@"

re: clean all

norme:
	norminette include src lib*/{include,src}

-include $(DEP)

ifndef VERBOSE
 ifndef TRAVIS
.SILENT:
 endif
endif

.PHONY: all, dev, san, $(PROJECTA), $(PROJECTB), clean, fclean, re, test, norme
