/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:02 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/23 19:55:21 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_ld(t_proc *proc, uint8_t *pc)
{
	uint8_t		*ptr;
	int32_t		a1;
	uint8_t		reg;

	ptr = cw_move_ptr(pc, 2);
	a1 = cw_read_arg(proc, &ptr, 0, F_IND_RESTRICT | F_DIR_DOUBLE);
	reg = cw_read_arg(proc, &ptr, 1, F_REG);
	if (!reg || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[reg] = a1;
	cw_update_carry(proc, proc->reg[reg]);
	proc->pc = cw_move_ptr(pc, ptr - pc);
	return (EXIT_SUCCESS);
}
/*
int			cw_ld(t_proc *proc, uint8_t *op_code)
{
	int				reg;
	uint32_t		value;
	uint8_t			mem[4];
	uint8_t			*ptr;

	ptr = cw_move_ptr(op_code, 2);
	if ((ft_mtoi(cw_map_mem(mem, cw_move_ptr(op_code, 1)), 1) >> 6) == DIR_CODE)
		value = cw_mem_read(&ptr, op_code, 4, F_DIR_DOUBLE);
	else
		value = cw_mem_read(&ptr, op_code, 2, F_IND_RESTRICT);
	reg = ft_mtoi(cw_map_mem(mem, ptr), 1);
	if (!reg || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[reg] = value;
	if (!value)
		proc->flags |= _CW_CARRY;
	else
		proc->flags &= ~(_CW_CARRY);
	proc->pc = cw_move_ptr(ptr, 1);
	return (EXIT_SUCCESS);
}
*/
