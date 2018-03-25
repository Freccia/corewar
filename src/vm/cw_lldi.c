/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:13:09 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/25 01:06:40 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_lldi(t_proc *proc, uint8_t *op_code)
{
	uint8_t		*ptr;
	uint8_t		*read;
	uint32_t	a[2];
	uint8_t		reg;

	ptr = cw_move_ptr(op_code, 2);
	a[0] = cw_read_arg(proc, &ptr, 0, F_IND | F_DIR | F_REG_VAL);
	a[1] = cw_read_arg(proc, &ptr, 1, F_IND | F_DIR);
	reg = cw_read_arg(proc, &ptr, 2, F_REG);
	if (!reg || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	read = cw_move_ptr(op_code, a[0] + a[1]);
	proc->reg[reg] = cw_read_nbytes(read, sizeof(int32_t));
	cw_update_carry(proc, g_cw->current->reg[reg]);
	proc->pc = cw_move_ptr(op_code, 8);
	return (EXIT_SUCCESS);
}
