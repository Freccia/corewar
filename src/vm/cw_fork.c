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

int			cw_fork(t_proc *proc, uint8_t *pc)
{
	t_proc		new;
	uint8_t		*ptr;
	int32_t		n;

	ptr = cw_move_ptr(pc, 1);
	n = cw_read_nbytes(ptr, 2);
	vm_procfork(&new, proc, cw_move_ptr(pc, n)); //TODO: lfabbro: % IDX_MOD));
	vm_procspush(&g_cw->procs, &new);
	proc->pc = cw_move_ptr(pc, 3);
	return (EXIT_SUCCESS);
}
