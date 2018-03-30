/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:08:36 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/27 10:27:21 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_add(t_proc *proc, uint8_t *pc)
{
	uint8_t *ptr;
	int32_t av[3];

	ptr = vm_move(pc, 2, FALSE);
	av[0] = vm_readarg(proc, &ptr, 0, F_REG_VAL | F_IND);
	av[1] = vm_readarg(proc, &ptr, 1, F_REG_VAL | F_IND);
	av[2] = vm_readarg(proc, &ptr, 2, F_REG | F_IND);
	proc->pc = ptr;
	if (av[2] < 0x1 || av[2] > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[av[2]] = av[0] + av[1];
	vm_carry(proc, proc->reg[av[2]]);
	return (EXIT_SUCCESS);
}
