/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:58:23 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/15 18:10:37 by nfinkel          ###   ########.fr       */
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

//todo: delete me -- use  g_op_tab
uint16_t				cw_instr_cycles(uint8_t instr)
{
	static int	instr_cycles[16] = {10, 5, 5, 10, 10, 6, 6, 6, 
		20, 25, 25, 800, 10, 50, 1000, 2};

	return (instr_cycles[instr]);
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
	size_t		k;

	k = -1;
	while (++k < len)
		if (pc == &g_cw->mem[MEM_SIZE - 1])
			pc = &g_cw->mem[0];
		else
			++pc;
	return (pc);
}

inline int				cw_mem_read(uint8_t *pc, size_t len, size_t move,
						t_range range)
{
	uint8_t		mem[4];
	uint8_t		*pos;

	pc = cw_move_pc(pc, move);
	if (range == E_SHORT)
		pos = cw_move_pc(pc, ft_mtoi(cw_map_mem(mem, pc), len) % IDX_MOD);
	else
		pos = cw_move_pc(pc, ft_mtoi(cw_map_mem(mem, pc), len));
	return (ft_mtoi(pos, len));
}
