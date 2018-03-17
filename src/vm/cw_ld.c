/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:02 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/16 20:15:03 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int					cw_ld(uint8_t *ocp)
{
	int			reg;
	int			value;
	uint8_t		mem[4];
	uint8_t		*ptr;

	ptr = ocp;
	if ((ft_mtoi(ocp, 1) & 0xc0) >> 6 | T_DIR)
		value = cw_mem_read_dir(&ocp, 4, 1, E_SHORT);
	else
		value = cw_mem_read_ind(&ocp, 2, 1, E_SHORT);
	reg = ft_mtoi(cw_map_mem(mem, ocp), 1);
	if (!reg || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	ft_memmove(g_cw->current->reg[reg], &value, REG_SIZE);
	if (!value)
		g_cw->current->flags |= _CW_CARRY;
	else
		g_cw->current->flags &= ~(_CW_CARRY);
	g_cw->current->pc = cw_mem_inc(ocp, ocp - ptr);
	return (EXIT_SUCCESS);
}
