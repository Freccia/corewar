/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 18:21:04 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/14 04:18:07 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H

# include "asm/asm_util.h"
# include "op.h"

# define MAX_ARG_LENGTH		(MAX_LABEL_LENGTH + 3)
# define MAX_LABEL_LENGTH	23
# define MAX_OP_CODE_LENGTH	7

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
** globad
*/
extern t_arr			*g_cor;
extern t_htable			*g_labels;

/*
** init_data.c
*/
void					init_data(void);

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
