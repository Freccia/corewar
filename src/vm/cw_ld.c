/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:02 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/15 18:11:27 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int					cw_ld(uint8_t *pc)
{
	int			reg;
	int			value;
	uint8_t		mem[4];

	if (ft_mtoi(mem, 1) == (T_DIR | T_REG))
	{
		value = cw_mem_read(pc, 4, 1, E_SHORT);
		pc = cw_move_pc(pc, 5);
	}
	else
	{
		value = cw_mem_read(pc, 2, 1, E_SHORT);
		pc = cw_move_pc(pc, 3);
	}
	reg = ft_mtoi(cw_map_mem(mem, pc), 1);
	if (!reg || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	ft_memcpy(g_cw->current->reg[reg], &value, REG_SIZE);
	if (!value)
		g_cw->current->flags |= _CW_CARRY;
	else
		g_cw->current->flags &= ~(_CW_CARRY);
	return (EXIT_SUCCESS);
}
