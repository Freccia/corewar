/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:16:28 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/25 20:15:31 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern const t_args		g_arg[MAX_ARGS_NUMBER + 1];

int			cw_st(t_proc *proc, uint8_t *op_code)
{
	uint8_t		*ptr;
	uint8_t		*ocp;
	uint8_t		*tmp;
	int32_t		dst;
	int32_t		value;

	ptr = cw_move_ptr(op_code, 2);
	value = cw_read_arg(proc, &ptr, 0, F_REG_VAL);
	cw_update_carry(proc, value);
	ocp	= cw_move_ptr(op_code, 1);
	if ((*ocp & g_arg[1].mask) >> g_arg[1].shift == REG_CODE)
	{
		dst = cw_read_arg(proc, &ptr, 1, F_REG);
		proc->reg[dst] = value;
	}
	else if ((*ocp & g_arg[1].mask) >> g_arg[1].shift == IND_CODE)
	{
		dst = cw_read_n(ptr, 2);
		ptr = cw_move_ptr(ptr, 2);
		tmp = cw_move_ptr(op_code, dst % IDX_MOD);
		value = swap_uint32(value);
		cw_mem_cpy(tmp, (uint8_t *)&value, sizeof(int32_t), proc->color + 2);
	}
	proc->pc = cw_move_ptr(op_code, ptr - op_code);
	return (0);
}
