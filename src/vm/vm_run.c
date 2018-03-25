/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:55:56 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/25 03:14:43 by lfabbro          ###   ########.fr       */
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
}

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

#define BUFF_SIZE 256
void	cw_verbose(const t_proc *proc, const char *name, int id, t_verbose flag)
{
	char		s[BUFF_SIZE];

	if (flag == E_VALID_LIVE)
		ft_printf("Player %s [%hd] is alive!\n", name, id);
	else if (flag == E_CYCLE)
		ft_printf("It is now cycle %d\n", g_cw->cycle);
	else if (flag == E_DELTA)
		ft_printf("Cycle to die is now %d\n", g_cw->cycle_to_die);
	else
	{
		ft_snprintf(s, BUFF_SIZE, "Process %d [%s]", proc->pid, name);
		if (flag == E_INVALID_LIVE)
			ft_printf("%s made a live... But nobody came.\n", s);
		else if (flag == E_OP)
			ft_printf("%s is executing %s\n", s, g_op_tab[*proc->pc - 1].name);
		else if (flag == E_DEATH)
			ft_printf("%s hasn't lived for %d cycles... Fuck off!", s,\
				g_cw->cycle - proc->lastlive);
//		else if (opt.v & 16 && flag == E_MOVE)
//			ft_printf("%s is moving! ADV %d (%.4p -> %.4p)", s, proc->id, name,\
//				id, 0, 0); TODO proper calc
	}
}

int		cw_vm_exec(t_proc *proc, uint8_t *pc)
{
	if (*pc >= 0x1 && *pc <= MAX_OP && *pc == g_op_tab[*pc - 1].op_code)
	{
		if (!g_op_tab[*pc - 1].ocp || cw_check_ocp(pc) == EXIT_SUCCESS)
		{
			cw_nc_notify(pc - g_cw->mem, g_cw->current->color, *pc);
			g_instr[*pc - 1](proc, pc);
			cw_nc_notify(g_cw->current->pc - g_cw->mem,\
				g_cw->current->color + 5, *g_cw->current->pc);
			if (g_cw->opt.v & 4)
				cw_verbose(proc, "PUT CHAMP NAME", 0, E_OP);
			return (EXIT_SUCCESS);
		}
		else
			proc->crashed = E_WRONG_OCP;
	}
	else
		proc->crashed = E_WRONG_OP;
	return (EXIT_FAILURE);
}

void	cw_vm_eval(t_proc *proc)
{
	if (proc->wait > 1)
		--proc->wait;
	else if (cw_vm_exec(proc, proc->pc) == EXIT_SUCCESS)
	{
		proc->wait = g_op_tab[*proc->pc - 1].cycles - 1;
	}
	else if (*proc->pc >= 0x1 && *proc->pc <= MAX_OP)
	{
		cw_nc_notify(proc->pc - g_cw->mem, proc->id, *proc->pc);
		proc->wait = g_op_tab[*proc->pc - 1].cycles;
	}
	else
	{
		// increment pc ?
		if (g_cw->opt.v & 8)
			cw_verbose(proc, "PUT CHAMP NAME", 0, E_DEATH);
		proc->wait = 1;
	}
}

int		cw_vm_run(void)
{
	while (g_cw->cycle_to_die > 0)
	{
		g_cw->current = g_cw->procs;
		++g_cw->cycle;
		if (g_cw->opt.v & 2)
			cw_verbose(NULL, NULL, 0, E_CYCLE);
		while (g_cw->current)
		{
			if (cw_nc_update())
				return (cw_exit(EXIT_FAILURE, NULL));
			cw_vm_eval(g_cw->current);
			g_cw->current = g_cw->current->next;
		}
		if (g_cw->opt.d > 0 && g_cw->cycle == g_cw->opt.d)
		{
			cw_mem_dump(&g_cw->mem[0]);
			return (cw_exit(EXIT_SUCCESS, NULL));
		}
		if (g_cw->cycle == g_cw->cycle_to_die)
		{
		//	cw_vm_cycle_to_die();
			g_cw->cycle = 0;
			g_cw->cycle_to_die -= CYCLE_DELTA;
			if (g_cw->opt.v & 2)
				cw_verbose(NULL, NULL, 0, E_DELTA);
		}
	}
	// TODO: who won?
	return (EXIT_SUCCESS);
}
