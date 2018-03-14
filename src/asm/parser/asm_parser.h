/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 18:21:04 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/19 20:44:41 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_PARSER_H

# define ASM_PARSER_H

# include "asm.h"


/*
** parse_args.c
*/
void				parse_args(t_instruct_read *instruct_r, \
							   t_instruct_parsed *instruct_p);

#endif
