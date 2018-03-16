/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:58:23 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/16 18:29:54 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void					cw_mem_cpy(uint8_t *mem, uint8_t const *src, size_t len,
						uint16_t p)
{
	while (len)
	{
		cw_nc_notify((uint16_t)(mem - g_cw->mem), p, *src);
		*mem++ = *src++;
		--len;
	}
}

void					cw_mem_dump(uint8_t *mem)
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

inline uint8_t			*cw_map_mem(uint8_t *mem, uint8_t *pc)
{
	uint8_t		k;

	ft_memset(mem, '\0', 4 * sizeof(uint8_t));
	k = -1;
	while (++k < 4)
	{
		mem[k] = *pc;
		if (pc == &g_cw->mem[MEM_SIZE - 1])
			pc = &g_cw->mem[0];
		else
			++pc;
	}
	return (mem);
}

inline uint8_t			*cw_move_pc(uint8_t *pc, size_t len)
{
	return (pc + (size_t)((pc - g_cw->mem + len) % MEM_SIZE));
}

inline int				cw_mem_read_dir(uint8_t **pc, size_t len, size_t move,
						t_range range)
{
	uint8_t		mem[4];
	uint8_t		*pos;

	if (move)
		*pc = cw_move_pc(*pc, move);
	if (range == E_SHORT)
		pos = &g_cw->mem[ft_mtoi(cw_map_mem(mem, *pc), len) % IDX_MOD];
	else
		pos = &g_cw->mem[ft_mtoi(cw_map_mem(mem, *pc), len)];
	*pc = cw_move_pc(*pc, len);
	return (ft_mtoi(cw_map_mem(mem, pos), len));
}

inline int				cw_mem_read_ind(uint8_t **pc, size_t len, size_t move,
						t_range range)
{
	uint8_t		mem[4];
	uint8_t		*pos;

	if (move)
		*pc = cw_move_pc(*pc, move);
	if (range == E_SHORT)
		pos = cw_move_pc(*pc, ft_mtoi(cw_map_mem(mem, *pc), len) % IDX_MOD);
	else
		pos = cw_move_pc(*pc, ft_mtoi(cw_map_mem(mem, *pc), len));
	*pc = cw_move_pc(*pc, len);
	return (ft_mtoi(cw_map_mem(mem, pos), len));
}
