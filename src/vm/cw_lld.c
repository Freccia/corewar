/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:12:49 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/23 15:08:11 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_lld(t_proc *proc, uint8_t *op_code)
{
	int			reg;
	size_t		value;
	uint8_t		mem[4];
	uint8_t		*ptr;

	ptr = cw_move_ptr(op_code, 2);
	if ((ft_mtoi(cw_move_ptr(op_code, 1), 1) >> 6) == DIR_CODE)
		value = cw_mem_read(&ptr, op_code, 4, F_DIR_DOUBLE);
	else
		value = cw_mem_read(&ptr, op_code, 2, F_IND);
	reg = ft_mtoi(cw_map_mem(mem, ptr, sizeof(mem)), 1);
	if (!reg || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[reg] = value;
	cw_update_carry(proc, value);
	proc->pc = cw_move_ptr(ptr, 1);
	return (EXIT_SUCCESS);
}
