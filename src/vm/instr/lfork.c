/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:33 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/25 03:11:52 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_lfork(t_proc *proc, uint8_t *pc)
{
	t_proc		new;
	uint8_t		*it;
	int32_t		n;

	it = cw_move_ptr(pc, 1);
	n = cw_read_nbytes(it, 2);
	vm_procfork(&new, proc, cw_move_ptr(pc, n));
	vm_procspush(&g_vm->procs, &new);
	proc->pc = cw_move_ptr(pc, 3);
	return (EXIT_SUCCESS);
}
