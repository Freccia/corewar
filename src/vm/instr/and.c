/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:09:37 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/27 10:36:24 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_and(t_proc *proc, uint8_t *pc)
{
	uint8_t		*ptr;
	uint32_t	a[2];
	uint8_t		reg;

	ptr = cw_move_ptr(pc, 2);
	a[0] = cw_read_arg(proc, &ptr, 0, F_IND_RESTRICT | F_DIR_LONG | F_REG_VAL);
	a[1] = cw_read_arg(proc, &ptr, 1, F_IND_RESTRICT | F_DIR_LONG | F_REG_VAL);
	reg = cw_read_arg(proc, &ptr, 2, F_REG);
	if (reg < 0x1 || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[reg] = a[0] & a[1];
	cw_update_carry(proc, proc->reg[reg]);
	//proc->pc = cw_move_ptr(pc, ptr - pc);
	proc->pc = ptr;
	return (EXIT_SUCCESS);
}
