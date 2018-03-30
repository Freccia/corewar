/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:58:23 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/30 18:12:33 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		vm_write(uint8_t *dst, uint8_t *src, size_t len, int color)
{
	while (len--)
	{
		*dst = *src;
		if (!g_vm->cycle_total)
			vm_guinotify((uint16_t)(dst - g_vm->mem), color, 0, 0);
		else
			vm_guinotify((uint16_t)(dst - g_vm->mem), color, GUI_BOLD, 80);
		++src;
		dst = vm_move(dst, 1, FALSE);
	}
}

uint8_t		*vm_map(uint8_t *mem, uint8_t *pc, uint16_t n)
{
	uint8_t	k;

	ft_memset(mem, '\0', n * sizeof(uint8_t));
	k = 0;
	while (k < n)
	{
		mem[k++] = *pc;
		pc = vm_move(pc, 1, FALSE);
	}
	return (mem);
}

uint8_t		*vm_move(uint8_t const *pc, int32_t move, int idx_res)
{
	int32_t		abs;
	t_proc		*proc;

	if (idx_res)
		move %= IDX_MOD;
	abs = (int32_t)(pc - g_vm->mem + move);
	if (!g_vm->opt.ctmo)
	{
		if (abs < 0)
			abs = MEM_SIZE + abs;
		return (g_vm->mem + (abs % MEM_SIZE));
	}
	else
	{
		if (abs < 0)
			abs = (MEM_SIZE / g_vm->players.len) + abs;
		proc = g_vm->procs.current;
		return (proc->ctmo_mem_start + (abs % (MEM_SIZE / g_vm->players.len)));
	}
}
