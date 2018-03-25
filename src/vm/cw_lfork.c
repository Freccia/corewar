/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:33 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/25 20:15:48 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_lfork(t_proc *proc, uint8_t *op_code)
{
	uint8_t		*ptr;
	int16_t		n;
	t_proc		*new;

	ptr = cw_move_ptr(op_code, 1);
	n = cw_read_n(ptr, 2);
	new = ft_malloc(sizeof(t_proc));
	ft_memcpy(new, proc, sizeof(t_proc));
	new->lastlive = 0;
	new->wait = 1;
	//if (*proc->pc >= 1 && *proc->pc <= MAX_OP)
	//	new->wait = g_op_tab[*proc->pc - 1].cycles - 1;
	new->pc = cw_move_ptr(op_code, n);
	proc->pc = cw_move_ptr(op_code, 3);
	new->next = g_cw->procs;
	g_cw->procs = new;
	++g_cw->proc_count;
	return (0);
}
