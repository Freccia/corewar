/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:02 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/17 20:15:27 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_ld(uint8_t *op_code)
{
	int			reg;
	size_t		value;
	uint8_t		mem[4];
	uint8_t		*ptr;

	ptr = cw_move_ptr(op_code, 2);
	if ((ft_mtoi(cw_move_ptr(op_code, 1), 1) >> 6) == DIR_CODE)
		value = cw_mem_read(&ptr, op_code, 4, E_DIR);
	else
		value = cw_mem_read(&ptr, op_code, 2, E_IND_SHORT);
	reg = ft_mtoi(cw_map_mem(mem, ptr), 1);
	if (!reg || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	ft_memmove(g_cw->current->reg[reg], &value, REG_SIZE);
	if (!value)
		g_cw->current->flags |= _CW_CARRY;
	else
		g_cw->current->flags &= ~(_CW_CARRY);
	g_cw->current->pc = cw_move_ptr(ptr, 1);
	return (EXIT_SUCCESS);
}
