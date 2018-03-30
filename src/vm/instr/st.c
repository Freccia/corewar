/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:16:28 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/30 19:14:16 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	streg(t_proc *proc, uint8_t *ptr, int32_t val)
{
	int32_t dst;

	dst = vm_readarg(proc, &ptr, 1, F_REG);
	proc->pc = ptr;
	if (dst < 0x1 || dst > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[dst] = val;
	return (EXIT_SUCCESS);
}

static int	stind(t_proc *proc, uint8_t *pc, uint8_t *ptr, int32_t val)
{
	int32_t dst;
	uint8_t *write;

	dst = vm_read(ptr, 2);
	ptr = vm_move(ptr, 2, FALSE);
	write = vm_move(pc, dst, TRUE);
	val = swap_uint32((uint32_t)val);
	vm_write(write, (uint8_t *)&val, sizeof(int32_t), proc->owner->idx + 1);
	proc->pc = ptr;
	return (EXIT_SUCCESS);
}

int			vm_st(t_proc *proc, uint8_t *pc)
{
	uint8_t *ptr;
	uint8_t *ocp;
	int32_t val;

	ptr = vm_move(pc, 2, FALSE);
	ocp = vm_move(pc, 1, FALSE);
	val = vm_readarg(proc, &ptr, 0, F_REG_VAL);
	if ((*ocp & g_arg[1].mask) >> g_arg[1].shift == REG_CODE)
		return (streg(proc, ptr, val));
	else if ((*ocp & g_arg[1].mask) >> g_arg[1].shift == IND_CODE)
		return (stind(proc, pc, ptr, val));
	return (EXIT_SUCCESS);
}
