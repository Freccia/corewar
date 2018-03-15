/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 18:21:04 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/15 01:37:05 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H

# include "libft.h"
# include "op.h"

# define ANNOYING_DEBUG         /* DEBUG */
# ifdef ANNOYING_DEBUG
#  include <stdio.h>
#  define CLR_BLACK "\033[30;01m"
#  define CLR_RED "\033[31;01m"
#  define CLR_GREEN "\033[32;01m"
#  define CLR_YELLOW "\033[33;01m"
#  define CLR_BLUE "\033[34;01m"
#  define CLR_MAGENTA "\033[35;01m"
#  define CLR_CYAN "\033[36;01m"
#  define CLR_WHITE "\033[37;01m"
#  define CLR_RESET "\033[0m"
#  define DEBUG_HEADER CLR_MAGENTA "[DEBUG] " CLR_RESET
#  define DEBUGF(str, ...) fprintf(stderr, DEBUG_HEADER "<" str ">" CLR_RESET "\n", ##__VA_ARGS__)
# else
#  define DEBUGF(str, ...) do {} while (0)
# endif

# define MAX_ARG_LENGTH		(MAX_LABEL_LENGTH + 3)
# define MAX_LABEL_LENGTH	23
# define MAX_OP_CODE_LENGTH	7

/*
** some types for handling memory
*/
typedef unsigned char			t_byte;
typedef unsigned short			t_word;
typedef unsigned int			t_dword;

/*
** instruction struct (as read)
*/
typedef struct			s_instruct_read
{
	char				label[MAX_LABEL_LENGTH + 1];
	char				op[MAX_OP_CODE_LENGTH + 1];
	int					argc;
	char				argv[MAX_ARGS_NUMBER][MAX_ARG_LENGTH + 1];
}						t_instruct_read;

/*
** instruction struct (after parsing)
*/
typedef struct		s_instruct_parsed
{
	t_op				*op;
	t_arg_type			arg_type[MAX_ARGS_NUMBER];
	t_byte				arg_length[MAX_ARGS_NUMBER];
	t_dword				addr;
}					t_instruct_parsed;

/*
** error code enum
*/
enum					e_error
{
	E_NOERROR = 0,
	E_NOEXIT = (1 << 0),
	E_USAGE_COREWAR = (1 << 1),
	E_USAGE_ASM = (1 << 2),
	E_READ = (1 << 3),
	E_OPEN = (1 << 4),
	E_CLOSE = (1 << 5),
	E_INVALID = (1 << 6),
	E_WRITE = (1 << 7)
};

/*
** globad
*/
extern t_arr			*g_cor;
extern t_htable			*g_labels;
extern char				*g_exec_name;
extern int				g_fd;
extern t_op 			g_op_tab[];

/*
** init_data.c
*/
void					init_data(void);
void                    init_exec_name(char *s);

/*
** error.c
*/
t_bool					error(uint8_t flag, char *msg);

/*
** LEXER
** asm_lexer.c
*/
void					lex(char *filename);

/*
** read_instruction.c
*/
void					read_loop(void);

/*
** PARSER
** asm_parser.c
*/
void					parse_instruct(t_instruct_read *instruct);

/*
** ENCODER
** asm_encoder.c
*/
void					encode(t_instruct_read *instruct_r, \
							   t_instruct_parsed *instruct_p);
/*
**  write_cor.c
*/
void					write_cor(char *filename, t_header *header);

#endif
