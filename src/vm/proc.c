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
	ptr->pc = g_cw->mem + (owner->idx * (MEM_SIZE / g_cw->players.len));
	ptr->pid = ++g_cw->max_pid;
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
	dst->pid = ++g_cw->max_pid;
	dst->pc = pc;
}

void	vm_procspush(t_procs *procs, t_proc *proc)
{
	proc = ft_memdup(proc, sizeof(t_proc));
	proc->next = procs->head;
	procs->head = proc;
	++procs->len;
}

void	vm_procsrem(t_procs *procs, t_proc *proc)
{

}

