/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:55:56 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/30 11:54:24 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	advance(t_proc *proc)
{
	vm_guinotify((uint16_t)(proc->pc - g_vm->mem), -1, 0, 0);
	proc->pc = vm_move(proc->pc, 1, FALSE);
	vm_guinotify((uint16_t)(proc->pc - g_vm->mem), -1, GUI_INV, 0);
}

static void	exec(t_proc *proc)
{
	vm_guiproc(proc);
	if (proc->state == STATE_RUNNING || proc->state == STATE_PENDING)
	{
		if (*proc->pc < 0x1 || *proc->pc > MAX_OP)
			advance(proc);
		else
		{
			vm_guinotify((uint16_t)(proc->pc - g_vm->mem), -1, GUI_INV, 0);
			proc->wait = (uint16_t)(g_op_tab[*proc->pc - 1].cycles - 1);
			proc->state = STATE_WAITING;
		}
	}
	else if (proc->state == STATE_WAITING)
	{
		if (proc->wait > 1)
			--proc->wait;
		else
		{
			proc->state = STATE_RUNNING;
			vm_guinotify((uint16_t)(proc->pc - g_vm->mem), -1, 0, 0);
			if (vm_eval(proc, proc->pc))
				proc->state = STATE_PENDING;
			vm_guinotify((uint16_t)(proc->pc - g_vm->mem), -1, GUI_INV, 0);
		}
	}
}

static void	cycle_to_die(void)
{
	t_proc *proc;
	t_proc *next;

	g_vm->cycle = 0;
	g_vm->nbr_lives = 0;
	proc = g_vm->procs.head;
	while (proc)
	{
		next = proc->next;
		if (g_vm->cycle_total - proc->lastlive >= g_vm->cycle_to_die)
			vm_procsrem(&g_vm->procs, proc);
		else
			++g_vm->nbr_lives;
		proc = next;
	}
	++g_vm->max_checks;
	if (g_vm->nbr_lives >= NBR_LIVE || g_vm->max_checks == MAX_CHECKS)
	{
		g_vm->cycle_to_die -= CYCLE_DELTA;
		if (g_vm->opt.v & VM_VERB_CYCLE)
			ft_printf("Cycle to die is now %d\n", g_vm->cycle_to_die);
		g_vm->max_checks = 0;
	}
}

static void	who_won(void)
{
	t_player	*player;
	t_player	*winner;

	player = g_vm->players.head;
	winner = player;
	while (player)
	{
		if (player->lastlive > winner->lastlive)
			winner = player;
		player = player->next;
	}
	ft_printf("Contestant %d, \"%s\", has won !\n", winner->id, winner->name);
}

void		vm_run(void)
{
	t_proc *proc;
	t_proc *next;

	while (g_vm->cycle_to_die > 0 && g_vm->procs.len)
	{
		if (vm_guiupdate())
			vm_exit(EXIT_FAILURE, NULL);
		proc = g_vm->procs.head;
		++g_vm->cycle;
		++g_vm->cycle_total;
		if (g_vm->opt.v & VM_VERB_CYCLE)
			ft_printf("It is now cycle %d\n", g_vm->cycle_total);
		while (g_vm->procs.len && proc)
		{
			next = proc->next;
			exec(proc);
			proc->state == STATE_DIEING ? vm_procsrem(&g_vm->procs, proc) : 0;
			proc = next;
		}
		if (g_vm->opt.d > 0 && g_vm->cycle_total == g_vm->opt.d)
			return (vm_dump(&g_vm->mem[0]));
		if (g_vm->cycle >= g_vm->cycle_to_die)
			cycle_to_die();
	}
	who_won();
}
