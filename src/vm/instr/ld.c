/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:02 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/27 11:42:59 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_ld(t_proc *proc, uint8_t *pc)
{
	uint8_t *ptr;
	int32_t value;
	int32_t reg;

	ptr = vm_move(pc, 2, FALSE);
	value = vm_readarg(proc, &ptr, 0, F_IND_RESTRICT | F_DIR_LONG);
	reg = vm_readarg(proc, &ptr, 1, F_REG);
	proc->pc = ptr;
	if (reg < 0x1 || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[reg] = value;
	vm_carry(proc, value);
	return (EXIT_SUCCESS);
}
