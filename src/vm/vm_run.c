/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:55:56 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/17 17:21:29 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_instr		g_instr[MAX_OP]=
{
	cw_live,
	cw_ld,
	cw_st,
	cw_add,
	cw_sub,
	cw_and,
	cw_or,
	cw_xor,
	cw_zjmp,
	cw_ldi,
	cw_sti,
	cw_fork,
	cw_lld,
	cw_lldi,
	cw_lfork,
	cw_aff
};

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

int		cw_check_ocp(uint8_t *pc) // Segfault
{
/*	uint8_t		*ocp;

	ocp = cw_mem_inc(pc, 1);
	if (!(((*ocp & 0xc0) >> 6) & g_op_tab[*pc].param_type[0]))
		return (EXIT_FAILURE);
	if (!(((*ocp & 0x30) >> 4) & g_op_tab[*pc].param_type[1]))
		return (EXIT_FAILURE);
	if (!(((*ocp & 0x0c) >> 2) & g_op_tab[*pc].param_type[2]))
		return (EXIT_FAILURE);*/
	(void)pc;
	return (EXIT_SUCCESS);
}

int		cw_vm_exec(uint8_t *pc)
{
	if (*pc >= 0x1 && *pc <= 0x10)
		if (!g_op_tab[*pc].ocp || cw_check_ocp(pc) == EXIT_SUCCESS)
		{
			//ft_printf("OCP: \n", g_instr[*pc](g_cw->current->pc));
			//g_cw->current->pc = cw_move_ptr(pc, 1);
			// TODO: update g_cw->current->pc
			return (g_instr[*pc - 1](cw_mem_inc(pc, 1)));
		}
	return (EXIT_FAILURE);
}

int		cw_vm_eval(t_proc *proc)
{
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
	size_t		cycle_total;

	cycle_total = 0; // A afficher dans le GUI a la place des cycles qui reset
	while (g_cw->cycle_to_die > 0)
	{
		g_cw->current = g_cw->procs;
		while (g_cw->current)
		{
			if (cw_nc_update())
				return (cw_exit(EXIT_FAILURE, NULL));
			if (g_cw->opt.d > 0 && g_cw->cycle == (size_t)g_cw->opt.d)
			{
				cw_mem_dump(&g_cw->mem[0]);
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
		++g_cw->cycle; // A-t-il encore une utilite ?
		++cycle_total;
	}
	return (EXIT_SUCCESS);
}
