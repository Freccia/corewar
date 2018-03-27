/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:55:56 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/27 13:57:47 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	eval(t_proc *proc)
{
	if (proc->wait > 1)
		--proc->wait;
	else if (vm_eval(proc, proc->pc) == EXIT_SUCCESS)
	{
		if (*proc->pc >= 0x1 && *proc->pc <= MAX_OP)
			proc->wait = (uint16_t)(g_op_tab[*proc->pc - 1].cycles - 1);
	}
	else
	{
		vm_guinotify((uint16_t)(proc->pc - g_vm->mem),
			(uint16_t)(proc->owner->idx + CW_GUI_COLOR_DFT), *proc->pc);
		proc->pc = cw_move_ptr(proc->pc, 1);
		vm_guinotify((uint16_t)(proc->pc - g_vm->mem),
			(uint16_t)(proc->owner->idx + CW_GUI_COLOR_INV), *proc->pc);
		if (g_vm->opt.v & VM_VERB_DEATH)
			ft_printf("Process %d [%s] hasn't lived for %d cycles... Fuck off!",
				proc->pid, proc->owner->name, g_vm->cycle - proc->lastlive);
		proc->wait = 1;
	}
}

int			vm_run(void)
{
	t_proc *proc;

	while (g_vm->cycle_to_die > 0 && g_vm->procs.len)
	{
		proc = g_vm->procs.head;
		++g_vm->cycle;
		if (g_vm->opt.v & VM_VERB_CYCLE)
			ft_printf("It is now cycle %d\n", g_vm->cycle);
		while (proc)
		{
			if (vm_guiupdate())
				return (vm_exit(EXIT_FAILURE, NULL));
			eval(proc);
			if (!g_vm->procs.len) // this (else) should never happen
				break ; // if it happens we should have other problems (see exec)
			proc = proc->next;
		}
		if (g_vm->opt.d > 0 && g_vm->cycle == (size_t)g_vm->opt.d)
			cw_mem_dump(&g_vm->mem[0]);
		if (g_vm->cycle == g_vm->cycle_to_die)
		{
		//	We kill processes here, not during execution
		//	cw_vm_cycle_to_die();
			g_vm->cycle = 0;
			g_vm->cycle_to_die -= CYCLE_DELTA;
			if (g_vm->opt.v & VM_VERB_CYCLE)
				ft_printf("Cycle to die is now %d\n", g_vm->cycle_to_die);
		}
	}
	// TODO: who won?
	return (EXIT_SUCCESS);
}
