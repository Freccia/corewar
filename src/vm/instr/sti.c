/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:16:47 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/27 10:54:01 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_sti(t_proc *proc, uint8_t *pc)
{
	uint8_t		*ptr;
	uint8_t		*write;
	int32_t		av[2];
	int32_t		val;

	ptr = vm_move(pc, 2);
	val = vm_readarg(proc, &ptr, 0, F_REG_VAL);
	av[0] = vm_readarg(proc, &ptr, 1, F_IND_RESTRICT | F_DIR | F_REG_VAL);
	av[1] = vm_readarg(proc, &ptr, 2, F_DIR | F_REG_VAL);
	write = vm_move(pc, (av[0] + av[1]));// % IDX_MOD);
	val = swap_uint32((uint32_t)val);
	vm_write(write, (uint8_t *)&(val), sizeof(int32_t),
		(uint16_t)(proc->owner->idx + VM_COLOR_HINT));
	vm_carry(proc, val);
	//proc->pc = cw_move_ptr(pc, ptr - pc);
	proc->pc = ptr;
	return (EXIT_SUCCESS);
}
