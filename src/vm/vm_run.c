/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:55:56 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/19 17:40:43 by lfabbro          ###   ########.fr       */
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

/*int		cw_vm_kill_process(t_proc **proc, t_proc *prev)
{
	if ((*proc)->next != NULL && prev != *proc)
		prev->next = (*proc)->next;
	if (*proc == g_cw->procs)
		g_cw->procs = (*proc)->next;
	free(*proc);
	*proc = NULL;
	return (EXIT_SUCCESS);
}*/

int		cw_check_arg(uint8_t op, uint8_t ocp, uint8_t n_arg)
{
	uint8_t		arg_type;

	arg_type = g_op_tab[op].param_type[n_arg];
	if (arg_type == 0 && ocp == 0)
		return (EXIT_SUCCESS);
	else if ((arg_type & T_REG) && (ocp & REG_CODE))
		return (EXIT_SUCCESS);
	else if ((arg_type & T_DIR) && (ocp & DIR_CODE))
		return (EXIT_SUCCESS);
	else if ((arg_type & T_IND) && (ocp & IND_CODE))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		cw_check_ocp(uint8_t *pc)
{
	uint8_t		*ocp; //

	ocp = cw_move_ptr(pc, 1);
	//ft_printf("OCP: %d\n", *ocp);
	if (cw_check_arg((*pc - 1), ((*ocp & 0xc0) >> 6), 0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (cw_check_arg((*pc - 1), ((*ocp & 0x30) >> 4), 1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (cw_check_arg((*pc - 1), ((*ocp & 0x0c) >> 2), 2) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	//ft_printf("OCP OK\n");
	return (EXIT_SUCCESS);
}

int		cw_vm_exec(t_proc *proc, uint8_t *pc)
{
	if (*pc >= 0x1 && *pc <= MAX_OP && *pc == g_op_tab[*pc - 1].op_code)
		if (!g_op_tab[*pc - 1].ocp || cw_check_ocp(pc) == EXIT_SUCCESS)
		{
			cw_nc_notify(pc - g_cw->mem, g_cw->current->color, *pc);
			g_instr[*pc - 1](proc, pc);
			cw_nc_notify(g_cw->current->pc - g_cw->mem,\
				g_cw->current->color + 5, *g_cw->current->pc);
			return (EXIT_SUCCESS);
		}
	return (EXIT_FAILURE);
}

void	cw_vm_eval(t_proc *proc)
{
	if (proc->wait > 1)
		--proc->wait;
	else if (cw_vm_exec(proc, proc->pc) == EXIT_FAILURE)
	{
		// L'update du curseur sur le GUI est foireux, mais le pc se deplace bien
		cw_nc_notify(proc->pc - g_cw->mem, 1, *proc->pc);
		// TODO: proc->pc is updated directly on each instruction (see: zjmp)
		//proc->pc = cw_move_ptr(proc->pc, 1);
		// TODO: wait must be equal to the next instruction cycles
		proc->wait = g_op_tab[*proc->pc].cycles;
		cw_nc_notify(proc->pc - g_cw->mem, 1, *proc->pc);
	}
	else if (*proc->pc >= 0x1 && *proc->pc <= MAX_OP)
		proc->wait = g_op_tab[*proc->pc - 1].cycles - 1;
	else
		proc->wait = 1;
}

void	cw_vm_cycle_to_die(void)
{
	t_proc		*ptr;
	t_proc		*tmp;

	ptr = g_cw->procs;
	tmp = NULL;
	while (ptr)
		if (!ptr->lastlive)
		{
			if (tmp)
				tmp->next = ptr->next;
			else
				g_cw->procs = ptr->next;
			free(ptr);
			ptr = (tmp) ? tmp : g_cw->procs;
		}
		else
		{
			ptr->lastlive = 0;
			tmp = ptr;
			ptr = ptr->next;
		}
	g_cw->cycle = 0;
	g_cw->cycle_to_die -= CYCLE_DELTA;
}

int		cw_vm_run(void)
{
	while (g_cw->cycle_to_die > 0)
	{
		g_cw->current = g_cw->procs;
		++g_cw->cycle;
		while (g_cw->current)
		{
			if (cw_nc_update())
				return (cw_exit(EXIT_FAILURE, NULL));
			cw_vm_eval(g_cw->current);
			g_cw->prev = g_cw->current;
			g_cw->current = g_cw->current->next;
		}
		if (g_cw->opt.d > 0 && g_cw->cycle == g_cw->opt.d)
		{
			cw_mem_dump(&g_cw->mem[0]);
			return (cw_exit(EXIT_SUCCESS, NULL));
		}
		if (g_cw->cycle == g_cw->cycle_to_die)
			cw_vm_cycle_to_die();
	}
	return (EXIT_SUCCESS);
}

