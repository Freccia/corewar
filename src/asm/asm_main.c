/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 00:12:49 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/14 22:14:44 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** this is the main...
*/

#include "asm.h"

int				main(int ac, char **av)
{
	init_exec_name(*av++);

	if (ac != 2)
		error(E_USAGE_ASM, NULL);

	if (!ft_strcmp("-h", *av))
		error(E_USAGE_ASM | E_NOEXIT, NULL);
	else
		lex(*av);

	return (EXIT_SUCCESS);
}
