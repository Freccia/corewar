/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:02 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/25 20:47:50 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_ld(t_proc *proc, uint8_t *op_code)
{
	uint8_t		reg;
	uint8_t		*ptr;
	int32_t		a1;

	ptr = cw_move_ptr(op_code, 2);
	a1 = cw_read_arg(proc, &ptr, 0, F_IND_RESTRICT | F_DIR_LONG);
	reg = cw_read_arg(proc, &ptr, 1, F_REG);
	if (!reg || reg > REG_NUMBER || proc->kill == TRUE)
		return (-1);
	proc->reg[reg] = a1;
	cw_update_carry(proc, proc->reg[reg]);
	proc->pc = cw_move_ptr(op_code, ptr - op_code);
	return (0);
}
