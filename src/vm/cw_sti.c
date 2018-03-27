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

int			cw_sti(t_proc *proc, uint8_t *pc)
{
	uint8_t		*ptr;
	uint8_t		*write;
	int32_t		a[2];
	int32_t		val;

	ptr = cw_move_ptr(pc, 2);
	val = cw_read_arg(proc, &ptr, 0, F_REG_VAL);
	a[0] = cw_read_arg(proc, &ptr, 1, F_IND_RESTRICT | F_DIR | F_REG_VAL);
	a[1] = cw_read_arg(proc, &ptr, 2, F_DIR | F_REG_VAL);
	write = cw_move_ptr(pc, (a[0] + a[1]));// % IDX_MOD);
	val = swap_uint32((uint32_t)val);
	cw_mem_cpy(write, (uint8_t*)&(val), sizeof(int32_t),
		(uint16_t)(proc->owner->idx + CW_GUI_COLOR_HINT));
	cw_update_carry(proc, val);
	//proc->pc = cw_move_ptr(pc, ptr - pc);
	proc->pc = ptr;
	return (EXIT_SUCCESS);
}
