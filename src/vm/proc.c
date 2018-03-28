/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/proc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:17:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/25 03:11:06 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_procinit(t_proc *proc, t_player *owner)
{
	ft_bzero(proc, sizeof(t_proc));
	proc->owner = owner;
	proc->pc = g_vm->mem + (owner->idx * (MEM_SIZE / g_vm->players.len));
	proc->reg[1] = owner->id;
	vm_write(proc->pc, owner->bin, owner->size,
		(uint16_t)(proc->owner->idx + VM_COLOR_DFT));
	if (*proc->pc >= 0x1 && *proc->pc <= REG_SIZE)
		proc->wait = (uint16_t)(g_op_tab[*proc->pc - 1].cycles);
	else
		proc->wait = 0;
}

void	vm_procfork(t_proc *dst, t_proc *src, uint8_t *pc)
{
	ft_memcpy(dst, src, sizeof(t_proc));
	dst->lastlive = 0;
	dst->pc = pc;
	if (*dst->pc >= 0x1 && *dst->pc <= REG_SIZE)
		dst->wait = (uint16_t)(g_op_tab[*dst->pc - 1].cycles);
	else
		dst->wait = 0;
}

void	vm_procspush(t_procs *procs, t_proc *proc)
{
	proc = ft_memdup(proc, sizeof(t_proc));
	proc->next = procs->head;
	procs->head = proc;
	++procs->len;
	proc->pid = ++procs->pids;
	vm_guinotify((uint16_t)(proc->pc - g_vm->mem),
		(uint16_t)(proc->owner->idx + VM_COLOR_INV), *proc->pc);
}

void	vm_procsrem(t_procs *procs, t_proc *proc)
{
	//TODO
	(void)procs;
	(void)proc;
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
