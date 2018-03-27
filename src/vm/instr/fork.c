/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:09:54 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/27 10:32:20 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_fork(t_proc *proc, uint8_t *pc)
{
	t_proc		new;
	uint8_t		*ptr;
	int32_t		n;

	ptr = vm_move(pc, 1, 0);
	n = vm_read(ptr, 2);
	vm_procfork(&new, proc, vm_move(pc, n, 1));
	vm_procspush(&g_vm->procs, &new);
	proc->pc = vm_move(pc, 3, 0);
	return (EXIT_SUCCESS);
}
