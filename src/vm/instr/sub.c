/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:17:09 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/27 10:54:34 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_sub(t_proc *proc, uint8_t *pc)
{
	uint8_t		*ptr;
	int32_t		av[3];

	ptr = vm_move(pc, 2, FALSE);
	av[0] = vm_readarg(proc, &ptr, 0, F_REG_VAL);
	av[1] = vm_readarg(proc, &ptr, 1, F_REG_VAL);
	av[2] = vm_readarg(proc, &ptr, 2, F_REG);
	if (av[2] < 0x1 || av[2] > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[av[2]] = av[0] - av[1];
	vm_carry(proc, proc->reg[av[2]]);
	proc->pc = vm_move(pc, 5, FALSE);
	return (EXIT_SUCCESS);
}
