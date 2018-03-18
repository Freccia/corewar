/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:16:28 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/18 15:12:32 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_st(t_proc *proc, uint8_t *op_code)
{
	int			reg;
	int			value;
	uint8_t		mem[4];
	uint8_t		*ptr;

	ptr = cw_move_ptr(op_code, 1);
	if (!(reg = ft_mtoi(cw_map_mem(mem, ptr), 1)) || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	ft_memmove(&value, proc->reg[reg], REG_SIZE);
	if (!value)
		proc->flags |= _CW_CARRY;
	else
		proc->flags &= ~(_CW_CARRY);
	proc->pc = cw_move_ptr(ptr, 1);
	return (EXIT_SUCCESS);
}
