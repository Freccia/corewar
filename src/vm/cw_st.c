/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:16:28 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/26 11:12:39 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern const t_args		g_arg[MAX_ARGS_NUMBER + 1];

int					cw_st(t_proc *proc, uint8_t *pc)
{
	uint8_t		*ptr;
	uint8_t		*ocp;
	uint8_t		*tmp;
	int32_t		dst;
	int32_t		value;

	ptr = cw_move_ptr(pc, 2);
	ocp	= cw_move_ptr(pc, 1);
	value = cw_read_arg(proc, &ptr, 0, F_REG_VAL);
	cw_update_carry(proc, value);
	if ((*ocp & g_arg[1].mask) >> g_arg[1].shift == REG_CODE)
	{
		dst = cw_read_arg(proc, &ptr, 1, F_REG);
		proc->reg[dst] = value;
	}
	else if ((*ocp & g_arg[1].mask) >> g_arg[1].shift == IND_CODE)
	{
		dst = cw_read_nbytes(ptr, sizeof(dst));
		ptr = cw_move_ptr(ptr, 2);
		tmp = cw_move_ptr(pc, dst);// % IDX_MOD);
		value = swap_uint32(value);
		cw_mem_cpy(tmp, (uint8_t *)&value, sizeof(value), proc->color + 2);
	}
	proc->pc = cw_move_ptr(pc, ptr - pc);
	return (EXIT_SUCCESS);
}
