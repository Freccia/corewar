/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:16:28 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/27 10:50:11 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int					vm_st(t_proc *proc, uint8_t *pc)
{
	uint8_t		*ptr;
	uint8_t		*ocp;
	int32_t		value;
	int32_t		dst;
	uint8_t		*write;

	ptr = vm_move(pc, 2);
	ocp	= vm_move(pc, 1);
	value = vm_readarg(proc, &ptr, 0, F_REG_VAL);
	vm_carry(proc, value);
	if ((*ocp & g_arg[1].mask) >> g_arg[1].shift == REG_CODE)
	{
		dst = vm_readarg(proc, &ptr, 1, F_REG);
		if (dst < 0x1 || dst > REG_NUMBER)
			return (EXIT_FAILURE);
		proc->reg[dst] = value;
	}
	else if ((*ocp & g_arg[1].mask) >> g_arg[1].shift == IND_CODE)
	{
		dst = vm_read(ptr, 2);
		ptr = vm_move(ptr, 2);
		write = vm_move(pc, dst);// % IDX_MOD);
		value = swap_uint32((uint32_t)value);
		vm_write(write, (uint8_t *)&value, sizeof(int32_t),
			(uint16_t)(proc->owner->idx + CW_GUI_COLOR_HINT));
	}
	//proc->pc = cw_move_ptr(pc, ptr - pc);
	proc->pc = ptr;
	return (EXIT_SUCCESS);
}
