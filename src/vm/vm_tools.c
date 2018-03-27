/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:58:23 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/27 12:29:03 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			cw_mem_cpy(uint8_t *dst, uint8_t *src, size_t len, uint16_t p)
{
	while (len--)
	{
		*dst = *src;
		vm_guinotify((uint16_t)(dst - g_vm->mem), p, *src);
		++src;
		dst = cw_move_ptr(dst, 1);
	}
}

void			cw_mem_dump(uint8_t *mem)
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
}

uint8_t			*cw_map_mem(uint8_t *mem, uint8_t *pc, uint16_t n)
{
	uint8_t		k;

	ft_memset(mem, '\0', n * sizeof(uint8_t));
	k = -1;
	while (++k < n)
	{
		mem[k] = *pc;
		pc = cw_move_ptr(pc, 1);
	}
	return (mem);
}

int32_t			cw_read_nbytes(uint8_t *ptr, uint16_t n)
{
	uint8_t		mem[n + 1];

	return (ft_mtoi(cw_map_mem(mem, ptr, n), n));
}

uint8_t			*cw_move_ptr(uint8_t const *pc, int32_t move)
{
	int32_t		abs;

	// OK, mais penser a rajouter en fonction de -ctmo
	abs = ABS(pc - g_vm->mem + move);
	return (g_vm->mem + (abs % MEM_SIZE));
}
