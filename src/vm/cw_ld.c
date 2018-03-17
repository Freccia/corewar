/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:02 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/17 19:50:02 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_ld(uint8_t *ocp)
{
	int			reg;
	int			value;
	uint8_t		mem[4];

	if ((ft_mtoi(ocp, 1) >> 6) == DIR_CODE)
		value = cw_mem_read(&ocp, 4, 1, E_DIR);
	else
		value = cw_mem_read(&ocp, 2, 1, E_IND_SHORT);
	reg = ft_mtoi(cw_map_mem(mem, ocp), 1);
ft_printf("%d\n", value);
	if (!reg || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	ft_memmove(g_cw->current->reg[reg], &value, REG_SIZE);
	if (!value)
		g_cw->current->flags |= _CW_CARRY;
	else
		g_cw->current->flags &= ~(_CW_CARRY);
	g_cw->current->pc = cw_move_ptr(ocp, 1);
	return (EXIT_SUCCESS);
}
