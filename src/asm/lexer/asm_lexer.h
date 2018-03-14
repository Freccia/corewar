/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_lexer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 18:21:04 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/14 05:21:42 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_LEXER_H

# define ASM_LEXER_H

# include "asm.h"

# define IS_EOL(c) (!c || c == COMMENT_CHAR)

/*
** lexing progress enum
*/

typedef enum		e_progress
{
	P_NOPROGRESS = 0,
	P_NAME = (1 << 0),
	P_COMMENT = (1 << 1),
	P_LABEL = (1 << 2),
	P_OP = (1 << 3),
	P_ARG = (1 << 4),
}					t_progress;

/*
** read_header.c
*/
void					read_header(t_header *header);

#endif
