/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/proc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:17:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/30 15:13:09 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_procinit(t_proc *proc, t_player *owner)
{
	ft_bzero(proc, sizeof(t_proc));
	proc->owner = owner;
	proc->pc = g_vm->mem + (owner->idx * (MEM_SIZE / g_vm->players.len));
	proc->reg[1] = owner->id;
	vm_write(proc->pc, owner->bin, owner->size, proc->owner->idx + 1);
	proc->lastlive = g_vm->cycle_total;
}

void	vm_procfork(t_proc *dst, t_proc *src, uint8_t *pc)
{
	ft_memcpy(dst, src, sizeof(t_proc));
	dst->lastlive = 0;
	dst->pc = pc;
	dst->state = STATE_PENDING;
	dst->lastlive = g_vm->cycle_total;
}

void	vm_procspush(t_procs *procs, t_proc *proc)
{
	proc = ft_memdup(proc, sizeof(t_proc));
	proc->next = procs->head;
	procs->head = proc;
	++procs->len;
	proc->pid = ++procs->max_pid;
	vm_guinotify((uint16_t)(proc->pc - g_vm->mem),
		-1, GUI_INV, 0);
}

void	vm_procsrem(t_procs *procs, t_proc *proc)
{
	t_proc	*ptr;
	void	*tmp;

	if (g_vm->opt.v & VM_VERB_DEATH)
		ft_printf("Process %d [%s] hasn't lived for %d cycles... Fuck off! "
			"-> Cycle to die was %d\n", proc->pid, proc->owner->name,
			g_vm->cycle_total - proc->lastlive, g_vm->cycle_to_die);
	vm_guinotify((uint16_t)(proc->pc - g_vm->mem), -1, 0, 0);
	--procs->len;
	if (procs->head == proc)
	{
		tmp = procs->head->next;
		free(procs->head);
		procs->head = (t_proc*)tmp;
		return ;
	}
	ptr = procs->head;
	while (ptr)
	{
		if (ptr->next == proc)
		{
			tmp = proc->next;
			free(proc);
			ptr->next = (t_proc*)tmp;
			return ;
		}
		ptr = ptr->next;
	}
}

void	vm_procsclr(t_procs *procs)
{
	t_proc	*proc;
	void	*tmp;

	proc = procs->head;
	while (proc)
	{
		tmp = proc->next;
		free(proc);
		proc = (t_proc *)tmp;
	}
	ft_bzero(procs, sizeof(t_procs));
}
