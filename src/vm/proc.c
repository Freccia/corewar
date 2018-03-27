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

void	vm_procinit(t_proc *ptr, t_player *owner)
{
	ft_bzero(ptr, sizeof(t_proc));
	ptr->owner = owner;
	ptr->pc = g_vm->mem + (owner->idx * (MEM_SIZE / g_vm->players.len));
	ptr->reg[1] = owner->id;
	cw_mem_cpy(ptr->pc, owner->bin, owner->size,
		(uint16_t)(ptr->owner->idx + CW_GUI_COLOR_DFT));
	ptr->wait = g_op_tab[*ptr->pc - 1].cycles;
}

void	vm_procfork(t_proc *dst, t_proc *src, uint8_t *pc)
{
	ft_memcpy(dst, src, sizeof(t_proc));
	dst->lastlive = 0;
	dst->wait = 1;
	dst->pc = pc;
}

void	vm_procspush(t_procs *procs, t_proc *proc)
{
	proc = ft_memdup(proc, sizeof(t_proc));
	proc->next = procs->head;
	procs->head = proc;
	++procs->len;
	proc->pid = ++procs->pids;
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
