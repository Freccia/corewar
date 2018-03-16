/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:02 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/16 15:12:23 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int					cw_ld(uint8_t *pc)
{
	int			reg;
	int			value;
	uint8_t		mem[4];

	if ((pc + 1) & _CW_FIRST_ARG & T_DIR)
		value = cw_mem_read_dir(&pc, 4, 1, E_SHORT);
	else // T_IND
		value = cw_mem_read_ind(&pc, 2, 1, E_SHORT);
	reg = ft_mtoi(cw_map_mem(mem, pc), 1);
	if (!reg || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	ft_memmove(g_cw->current->reg[reg], &value, REG_SIZE);
	if (!value)
		g_cw->current->flags |= _CW_CARRY;
	else
		g_cw->current->flags &= ~(_CW_CARRY);
	g_cw->current->pc = cw_move_pc(pc, 1);
	return (EXIT_SUCCESS);
}
