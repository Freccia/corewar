/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:02 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/18 16:20:51 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_ld(t_proc *proc, uint8_t *op_code)
{
	int			reg;
	size_t		value;
	uint8_t		mem[4];
	uint8_t		*ptr;

	ptr = cw_move_ptr(op_code, 2);
	if ((ft_mtoi(cw_map_mem(mem, cw_move_ptr(op_code, 1)), 1) >> 6) == DIR_CODE)
		value = cw_mem_read(&ptr, op_code, 4, E_DIR);
	else
		value = cw_mem_read(&ptr, op_code, 2, E_IND_SHORT);
	reg = ft_mtoi(cw_map_mem(mem, ptr), 1);
	if (!reg || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	ft_memmove(proc->reg[reg], &value, REG_SIZE);
	if (!value)
		proc->flags |= _CW_CARRY;
	else
		proc->flags &= ~(_CW_CARRY);
	proc->pc = cw_move_ptr(ptr, 1);
	return (EXIT_SUCCESS);
}
