/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:55:56 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/16 17:05:03 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		cw_vm_kill_process(t_proc **proc, t_proc *prev)
{
	if ((*proc)->next != NULL && prev != *proc)
		prev->next = (*proc)->next;
	if (*proc == g_cw->procs)
		g_cw->procs = (*proc)->next;
	free(*proc);
	*proc = NULL;
	return (EXIT_SUCCESS);
}

int		cw_check_ocp(uint8_t *pc)
{
	uint8_t		*ocp;

	g_cw->current->pc = cw_move_pc(pc, 1);
	ocp = g_cw->current->pc;
	if (!(((*ocp & 0xc0) >> 6) & g_op_tab[*pc].param_type[0]))
		return (EXIT_FAILURE);
	if (!(((*ocp & 0x30) >> 4) & g_op_tab[*pc].param_type[1]))
		return (EXIT_FAILURE);
	if (!(((*ocp & 0x0c) >> 2) & g_op_tab[*pc].param_type[2]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		cw_vm_exec(uint8_t *pc)
{
	if (*pc >= 0x1 && *pc <= 0x10)
		if (!g_op_tab[*pc].ocp || cw_check_ocp(pc) == EXIT_SUCCESS)
		{
			//ft_printf("OCP: \n", g_instr[*pc](g_cw->current->pc));
			return (g_instr[*pc](g_cw->current->pc));
		}
	return (EXIT_FAILURE);
}

int		cw_vm_eval(t_proc *proc)
{
	t_instr		instr;

	(void)instr;
	if (!proc)
		return (EXIT_SUCCESS);
	if (proc->wait > 0)
	{
		--proc->wait;
		return (EXIT_SUCCESS);
	}
	if (cw_vm_exec(proc->pc) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	proc->wait = g_op_tab[*proc->pc].cycles;
	return (EXIT_SUCCESS);
}

int		cw_vm_run(void)
{
	while (g_cw->cycle_to_die > 0)
	{
		g_cw->current = g_cw->procs;
		while (g_cw->current)
		{
			if (cw_nc_update())
				return (cw_exit(EXIT_FAILURE, NULL));
			if (g_cw->opt.d > 0 && g_cw->cycle == (size_t)g_cw->opt.d)
			{
				// todo: dump mem
				return (cw_exit(EXIT_SUCCESS, NULL));
			}
			if (cw_vm_eval(g_cw->current) == EXIT_FAILURE)
				cw_vm_kill_process(&g_cw->current, g_cw->prev);
			if (g_cw->cycle >= (size_t)g_cw->cycle_to_die)
			{
				g_cw->cycle = 0;
				g_cw->cycle_to_die -= CYCLE_DELTA;
			}
			g_cw->prev = g_cw->current;
			g_cw->current = g_cw->current->next;
		}
		++g_cw->cycle;
	}
	return (EXIT_SUCCESS);
}
