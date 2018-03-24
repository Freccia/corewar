/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:15:39 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/23 18:12:12 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_or(t_proc *proc, uint8_t *op_code)
{
	uint8_t		*ptr;
	uint32_t	a[2];
	uint8_t		reg;

	ptr = cw_move_ptr(op_code, 2);
	a[0] = cw_read_arg(proc, &ptr, 0, F_IND_RESTRICT | F_DIR_DOUBLE | F_REG_VAL);
	a[1] = cw_read_arg(proc, &ptr, 1, F_IND_RESTRICT | F_DIR_DOUBLE | F_REG_VAL);
	reg = cw_read_arg(proc, &ptr, 2, F_REG);
	if (!reg ||reg > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[reg] = a[0] | a[1];
	cw_update_carry(proc, proc->reg[reg]);
	proc->pc = cw_move_ptr(op_code, ptr - op_code);
	return (EXIT_SUCCESS);
}
