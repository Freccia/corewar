/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:18 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/27 12:49:47 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_ldi(t_proc *proc, uint8_t *pc)
{
	uint8_t *ptr;
	uint8_t *read;
	int32_t av[2];
	uint8_t reg;

	ptr = vm_move(pc, 2, FALSE);
	av[0] = vm_readarg(proc, &ptr, 0, F_IND_RESTRICT | F_DIR | F_REG_VAL);
	av[1] = vm_readarg(proc, &ptr, 1, F_IND_RESTRICT | F_DIR | F_REG_VAL);
	reg = (uint8_t)vm_readarg(proc, &ptr, 2, F_REG);
	proc->pc = vm_move(pc, (int32_t)(ptr - pc), FALSE);
	if (reg < 0x1 || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	read = vm_move(pc, (av[0] + av[1]), TRUE);
	proc->reg[reg] = vm_read(read, sizeof(proc->reg[1]));
	return (EXIT_SUCCESS);
}
