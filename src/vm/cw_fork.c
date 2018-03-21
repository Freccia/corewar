/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:09:54 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/21 20:41:36 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_fork(t_proc *proc, uint8_t *pc)
{
	t_proc		*new;
	t_proc		*tmp;
	uint8_t		*ptr;
	int32_t		n;

	ptr = cw_move_ptr(pc, 1);
	n = cw_mem_read(&ptr, pc, 1, F_DIR);
	if ((new = malloc(sizeof(t_proc))) == NULL)
		return (EXIT_FAILURE);
	tmp = g_cw->procs;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	ft_memcpy(new, proc, sizeof(t_proc));
	new->pc = cw_move_ptr(pc, n % IDX_MOD);
	new->next = NULL;
	proc->pc = cw_move_ptr(pc, 3);
	++g_cw->proc_count;
	return (EXIT_SUCCESS);
}
