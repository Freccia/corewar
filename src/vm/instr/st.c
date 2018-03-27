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

	ptr = cw_move_ptr(pc, 2);
	ocp	= cw_move_ptr(pc, 1);
	value = cw_read_arg(proc, &ptr, 0, F_REG_VAL);
	cw_update_carry(proc, value);
	if ((*ocp & g_arg[1].mask) >> g_arg[1].shift == REG_CODE)
	{
		dst = cw_read_arg(proc, &ptr, 1, F_REG);
		if (dst < 0x1 || dst > REG_NUMBER)
			return (EXIT_FAILURE);
		proc->reg[dst] = value;
	}
	else if ((*ocp & g_arg[1].mask) >> g_arg[1].shift == IND_CODE)
	{
		dst = cw_read_nbytes(ptr, 2);
		ptr = cw_move_ptr(ptr, 2);
		write = cw_move_ptr(pc, dst);// % IDX_MOD);
		value = swap_uint32((uint32_t)value);
		cw_mem_cpy(write, (uint8_t *)&value, sizeof(int32_t),
			(uint16_t)(proc->owner->idx + CW_GUI_COLOR_HINT));
	}
	//proc->pc = cw_move_ptr(pc, ptr - pc);
	proc->pc = ptr;
	return (EXIT_SUCCESS);
}
