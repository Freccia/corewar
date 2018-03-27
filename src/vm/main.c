/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/26 16:29:30 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_vm	g_vm_stack;
t_vm		*g_vm = &g_vm_stack;

int 		main(int ac, char **av)
{
	int r1;

	ft_bzero(g_vm, sizeof(t_vm));
	r1 = vm_optparse(&g_vm->opt, ac, av);
	if (vm_init(ac, av, r1))
		return (vm_exit(EXIT_FAILURE, NULL));
	if (vm_run())
		return (vm_exit(EXIT_FAILURE, NULL));
	return (vm_exit(EXIT_SUCCESS, NULL));
}
