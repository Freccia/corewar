/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 18:21:04 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/31 03:20:04 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H

# include "libft.h"
# include "op.h"
# include "cw_common.h"

# define MAX_ARG_LENGTH		(MAX_LABEL_LENGTH + 3)
# define MAX_LABEL_LENGTH	23
# define MAX_OP_CODE_LENGTH	7

# define ASM_EXTENSION "s"
# define COR_EXTENSION "cor"

/*
** some types for handling memory
*/
typedef unsigned char	t_byte;
typedef unsigned short	t_word;
typedef unsigned int	t_dword;

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
typedef struct			s_instruct_parsed
{
	t_op				*op;
	t_arg_type			arg_type[MAX_ARGS_NUMBER];
	t_byte				arg_length[MAX_ARGS_NUMBER];
	t_dword				addr;
	t_byte				padding[4];
}						t_instruct_parsed;

/*
** error reporting struct
*/
typedef struct			s_error_report
{
	char				*exec_name;
	char				*file_name;
	char				*line;
	unsigned int		line_pos;
	int					fd;
}						t_error_report;

/*
** error code enum
*/
enum					e_error
{
	E_NOERROR = 0,
	E_NOEXIT = (1 << 0),
	E_USAGE_ASM = (1 << 1),
	E_READ = (1 << 2),
	E_OPEN = (1 << 3),
	E_CLOSE = (1 << 4),
	E_WRITE = (1 << 5),
	E_INVALID = (1 << 6)
};

/*
** globad
*/
extern t_error_report	g_err;
extern t_arr			*g_cor;
extern t_htable			*g_labels;

/*
** init_data.c
*/
void					init_data(void);
void					init_error_report(char *exec_name);

/*
** error.c
*/
t_bool					error(t_byte flag, char *msg);

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
** write_cor.c
*/
void					write_cor(char *filename, t_header *header);

#endif
