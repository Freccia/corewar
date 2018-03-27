/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:58:23 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/27 12:29:03 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		vm_write(uint8_t *dst, uint8_t *src, size_t len, uint16_t p)
{
	while (len--)
	{
		*dst = *src;
		vm_guinotify((uint16_t)(dst - g_vm->mem), p, *src);
		++src;
		dst = vm_move(dst, 1, 0);
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
		pc = vm_move(pc, 1, 0);
	}
	return (mem);
}

uint8_t		*vm_move(uint8_t const *pc, int32_t move, uint8_t idx_mod)
{
	int32_t abs;

	abs = (int32_t)(pc - g_vm->mem + move);
	if (abs < 0)
		abs = -abs;
	if (idx_mod)
		return (g_vm->mem + (abs % IDX_MOD));
	return (g_vm->mem + (abs % MEM_SIZE));
}
