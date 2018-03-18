/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:12:49 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/18 14:57:29 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_lld(uint8_t *op_code)
{
	int			reg;
	size_t		value;
	uint8_t		mem[4];
	uint8_t		*ptr;

	ptr = cw_move_ptr(op_code, 2);
	if ((ft_mtoi(cw_move_ptr(op_code, 1), 1) >> 6) == DIR_CODE)
		value = cw_mem_read(&ptr, op_code, 4, E_DIR);
	else
		value = cw_mem_read(&ptr, op_code, 2, E_IND_LONG);
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
