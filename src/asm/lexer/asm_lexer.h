/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_lexer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 18:21:04 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/15 21:19:40 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_LEXER_H

# define ASM_LEXER_H

# include "asm.h"

/*
** open
*/
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/*
** close
*/
# include <unistd.h>

# define COMMENT_CHAR_B ';'
# define IS_EOL(c) (!c || c == COMMENT_CHAR || c == COMMENT_CHAR_B)

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
void				read_header(t_header *header);

#endif
