/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:58:23 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/21 19:22:20 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			cw_mem_cpy(uint8_t *dst, uint8_t *src, size_t len, uint16_t p)
{
	while (len--)
	{
		*dst = *src;
		cw_nc_notify((uint16_t)(dst - g_cw->mem), p, *src);
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

uint8_t			*cw_map_mem(uint8_t *mem, uint8_t *pc)
{
	uint8_t		k;

	ft_memset(mem, '\0', 4 * sizeof(uint8_t));
	k = -1;
	while (++k < 4)
	{
		mem[k] = *pc;
		pc = cw_move_ptr(pc, 1);
	}
	return (mem);
}

uint8_t			*cw_move_ptr(uint8_t const *pc, int32_t move)
{
	// OK, mais penser a rajouter en fonction de -ctmo
	return (g_cw->mem + ((pc - g_cw->mem + move) % MEM_SIZE));
}

uint32_t		cw_mem_read(uint8_t **ptr, uint8_t *pc, size_t len,
				uint32_t flags)
{
	uint8_t		mem[4];
	uint8_t		*pos;

	if (flags == F_DIR)
		pos = *ptr;
	else if (flags == F_IND_RESTRICT)
		pos = cw_move_ptr(pc, ft_mtoi(cw_map_mem(mem, *ptr), len) % IDX_MOD);
	else
		pos = cw_move_ptr(pc, ft_mtoi(cw_map_mem(mem, *ptr), len));
	*ptr = cw_move_ptr(*ptr, len);
	return (ft_mtoi(cw_map_mem(mem, pos), 4));
}
