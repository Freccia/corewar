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
	uint8_t *ptr;
	int32_t av[2];
	uint8_t reg;

	ptr = vm_move(pc, 2);
	av[0] = vm_readarg(proc, &ptr, 0, F_IND_RESTRICT | F_DIR_LONG | F_REG_VAL);
	av[1] = vm_readarg(proc, &ptr, 1, F_IND_RESTRICT | F_DIR_LONG | F_REG_VAL);
	reg = (uint8_t)vm_readarg(proc, &ptr, 2, F_REG);
	if (reg < 0x1 || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[reg] = av[0] & av[1];
	vm_carry(proc, proc->reg[reg]);
	//proc->pc = cw_move_ptr(pc, ptr - pc);
	proc->pc = ptr;
	return (EXIT_SUCCESS);
}
