/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:09:54 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/25 00:39:09 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_fork(t_proc *proc, uint8_t *op_code)
{
	t_proc		*new;
	uint8_t		*ptr;
	int16_t		n;

	ptr = cw_move_ptr(op_code, 1);
	n = cw_read_nbytes(ptr, 2);
	new = ft_malloc(sizeof(t_proc));
	ft_memcpy(new, proc, sizeof(t_proc));
	new->lastlive = 0;
	new->wait = 1;
	//if (*proc->pc >= 1 && *proc->pc <= MAX_OP)
	//	new->wait = g_op_tab[*proc->pc - 1].cycles - 1;
	new->pc = cw_move_ptr(op_code, n % IDX_MOD);
	proc->pc = cw_move_ptr(op_code, 3);
	new->next = g_cw->procs;
	g_cw->procs = new;
	++g_cw->proc_count;
	return (EXIT_SUCCESS);
}
