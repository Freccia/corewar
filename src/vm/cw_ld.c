/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:02 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/25 00:08:37 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_ld(t_proc *proc, uint8_t *pc)
{
	uint8_t		*ptr;
	int32_t		value;
	uint8_t		reg;

	ptr = cw_move_ptr(pc, 2);
	value = cw_read_arg(proc, &ptr, 0, F_IND_RESTRICT | F_DIR_DOUBLE);
	reg = cw_read_arg(proc, &ptr, 1, F_REG);
	if (!reg || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[reg] = value;
	cw_update_carry(proc, proc->reg[reg]);
	proc->pc = cw_move_ptr(pc, ptr - pc);
	return (EXIT_SUCCESS);
}
