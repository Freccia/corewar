/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 20:18:10 by mc                #+#    #+#             */
/*   Updated: 2018/03/24 20:21:55 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_lexer.h"

size_t		check_arg_len(size_t len, t_instruct_read *instruct)
{
	if (len > MAX_ARG_LENGTH)
		error(E_INVALID, "Invalid arg (too long).");
	if (instruct->argc + 1 > MAX_ARGS_NUMBER)
		error(E_INVALID, "Invalid arg (too many).");

	return (len);
}
