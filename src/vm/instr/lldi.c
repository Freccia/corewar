/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:13:09 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/27 10:42:33 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_lldi(t_proc *proc, uint8_t *pc)
{
	uint8_t *ptr;
	uint8_t *read;
	int32_t av[2];
	int32_t reg;

	ptr = vm_move(pc, 2, FALSE);
	av[0] = vm_readarg(proc, &ptr, 0, F_IND | F_DIR | F_REG_VAL);
	av[1] = vm_readarg(proc, &ptr, 1, F_IND | F_DIR);
	reg = vm_readarg(proc, &ptr, 2, F_REG);
	proc->pc = ptr;
	if (reg < 0x1 || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	read = vm_move(pc, av[0] + av[1], FALSE);
	proc->reg[reg] = vm_read(read, sizeof(proc->reg[1]));
	vm_carry(proc, proc->reg[reg]);
	return (EXIT_SUCCESS);
}
