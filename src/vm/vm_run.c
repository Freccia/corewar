/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:55:56 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/25 21:17:07 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			mem_dump(uint8_t *mem)
{
	int		k;
	int		p;
	int		q;

	k = -1;
	q = -40;
	ft_printf("0x");
	while (++k < MEM_SIZE / 64 && (p = -1))
	{
		ft_printf("%#.4x : ", (q += 40));
		while (++p < MEM_SIZE / 64)
			ft_printf("%.2x ", *mem++);
		ft_printf("\n");
	}
	cw_exit(EXIT_SUCCESS, NULL);
}

static void			kill_process(t_proc *proc)
{
	if (g_cw->opt.v & 8)
		cw_verbose(proc, "PUT CHAMP NAME", 0, E_DEATH);
	if (proc == g_cw->procs)
	{
		g_cw->procs = proc->next;
		g_cw->current = g_cw->procs;
	}
	else
	{
		g_cw->prev->next = proc->next;
		g_cw->current = proc->next;
	}
	ft_memdel((void **)&proc);
}

/*static void			check_live(t_cw *cw)
{
	t_proc		*ptr;
	t_proc		*tmp;

	ptr = cw->procs;
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
}*/

static void			eval(t_proc *proc)
{
	// TODO need to check cycle calculation versus zaz vm
	// TODO proper ncurses color update
	if (proc->wait > 1)
		--proc->wait;
	else if (*proc->pc >= 0x1 && *proc->pc <= MAX_OP)
	{
		if (!cw_vm_exec(proc, proc->pc))
			proc->wait = (*proc->pc >= 0x1 && *proc->pc <= MAX_OP ?\
				g_op_tab[*proc->pc - 1].cycles - 1 : 1);
		else
			kill_process(proc);
	}
	else
	{
		cw_nc_notify(proc->pc - g_cw->mem, proc->id, *proc->pc);
		proc->pc = cw_move_ptr(proc->pc, 1);
		proc->wait = 1;
	}
}

void				cw_vm_run(t_cw *cw)
{
	while (cw->cycle_to_die > 0 && ++cw->cycle && ++cw->total_cycles)
	{
		if (!(cw->current = cw->procs))
			break ;
		cw->opt.v & 2 ? cw_verbose(NULL, NULL, 0, E_CYCLE) : 0;
		while (cw->current)
		{
			if (cw_nc_update())
				cw_exit(EXIT_FAILURE, NULL);
			eval(cw->current);
			cw->prev = cw->current;
			if (cw->current)
				cw->current = cw->current->next;
		}
		if (cw->opt.d > 0 && cw->cycle == cw->opt.d)
			mem_dump(&cw->mem[0]);
		if (cw->cycle == cw->cycle_to_die)
		{
			//TODO check_live(cw);
			cw->cycle = 0;
			cw->cycle_to_die -= CYCLE_DELTA;
			cw->opt.v & 2 ? cw_verbose(NULL, NULL, 0, E_DELTA) : 0;
		}
	}
	//TODO display result
}
