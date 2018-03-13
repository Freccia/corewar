/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 00:12:49 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/19 20:04:08 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** this is the main...
*/

#include "asm.h"

char			*g_exec_name = NULL;
int				g_fd = -1;

int				main(int ac, char **av)
{
	g_exec_name = *av++;

	if (ac != 2)
		error(E_USAGE_ASM, NULL);

	if (!ft_strcmp("-h", *av))
		error(E_USAGE_ASM | E_NOEXIT, NULL);
	else
		lex(*av);

	return (EXIT_SUCCESS);
}
