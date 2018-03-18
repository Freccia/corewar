/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:16:28 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/18 18:37:58 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			do_copy(uint8_t *ptr, uint8_t *mem, uint8_t *op_code,
					uint32_t value)
{
	value = swap_uint32(value);
	ptr = cw_move_ptr(op_code, ft_mtoi(mem, 2) % IDX_MOD);
	cw_mem_cpy(ptr, (uint8_t *)&value, sizeof(uint32_t), g_cw->current->color);
}

int					cw_st(t_proc *proc, uint8_t *op_code)
{
	int			reg;
	uint32_t	value;
	uint8_t		mem[4];
	uint8_t		*ptr;

	ptr = cw_move_ptr(op_code, 2);
	if (!(reg = ft_mtoi(ptr, 1)) || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	if (!(value = proc->reg[reg]))
		proc->flags |= _CW_CARRY;
	else
		proc->flags &= ~(_CW_CARRY);
	ptr = cw_move_ptr(ptr, 1);
	if ((ft_mtoi(cw_move_ptr(op_code, 1), 1) & MASK_ARG2) >> 4 == REG_CODE)
	{
		proc->reg[ft_mtoi(ptr, 1)] = value;
		ptr = cw_move_ptr(ptr, 1);
	}
	else
		do_copy(ptr, cw_map_mem(mem, ptr), op_code, value);
	proc->pc = ptr;
	return (EXIT_SUCCESS);
}
