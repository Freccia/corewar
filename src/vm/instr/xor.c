/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:17:30 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/27 10:55:31 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_xor(t_proc *proc, uint8_t *pc)
{
	uint8_t		*ptr;
	int32_t		a[2];
	int8_t		reg;

	ptr = cw_move_ptr(pc, 2);
	a[0] = cw_read_arg(proc, &ptr, 0, F_IND_RESTRICT | F_DIR_LONG | F_REG_VAL);
	a[1] = cw_read_arg(proc, &ptr, 1, F_IND_RESTRICT | F_DIR_LONG | F_REG_VAL);
	reg = cw_read_arg(proc, &ptr, 2, F_REG);
	if (reg < 0x1 || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[reg] = a[0] ^ a[1];
	cw_update_carry(proc, proc->reg[reg]);
	//proc->pc = cw_move_ptr(pc, ptr - pc);
	proc->pc = ptr;
	return (EXIT_SUCCESS);
}
