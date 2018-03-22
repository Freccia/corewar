/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:09:54 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/22 00:34:24 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_fork(t_proc *proc, uint8_t *pc)
{
	t_proc		*new;
	uint8_t		*ptr;
	int32_t		n;

	ptr = cw_move_ptr(pc, 1);
	n = cw_read_arg(proc, &ptr, 0, F_DIR);
	ft_dprintf(1, "fork: %x\n", n);
	new = ft_malloc(sizeof(t_proc));
	new->next = g_cw->procs;
	g_cw->procs = new;
	ft_memcpy(new, proc, sizeof(t_proc));
	new->pc = cw_move_ptr(pc, n % IDX_MOD);
	new->next = NULL;
	proc->pc = cw_move_ptr(pc, 3);
	if (*proc->pc >= 1 && *proc->pc <= MAX_OP)
		new->wait = g_op_tab[*proc->pc - 1].cycles - 1;
	++g_cw->proc_count;
	return (EXIT_SUCCESS);
}
