/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:12:49 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/27 10:40:41 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_lld(t_proc *proc, uint8_t *pc)
{
	uint8_t		*ptr;
	int32_t		value;
	int32_t		reg;

	ptr = cw_move_ptr(pc, 2);
	value = cw_read_arg(proc, &ptr, 0, F_IND | F_DIR_LONG);
	reg = cw_read_arg(proc, &ptr, 1, F_REG);
	if (reg < 0x1 || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[reg] = value;
	cw_update_carry(proc, value);
	//proc->pc = cw_move_ptr(pc, ptr - pc);
	proc->pc = ptr;
	return (EXIT_SUCCESS);
}
