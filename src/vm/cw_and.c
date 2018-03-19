/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:09:37 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/19 20:29:29 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_and(t_proc *proc, uint8_t *pc)
{
	uint8_t		*ptr;
	uint32_t	a[2];
	uint8_t		reg;

	ptr = cw_move_ptr(pc, 2);
	a[0] = cw_read_arg(proc, &ptr, 0, E_IND_SHORT);
	a[1] = cw_read_arg(proc, &ptr, 1, E_IND_SHORT);
	ptr = cw_move_ptr(ptr, 1);
	reg = *ptr;
	if (!reg ||reg > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[reg] = a[0] & a[1];
	cw_update_carry(proc, proc->reg[reg]);
	proc->pc = cw_move_ptr(pc, ptr - pc + 1);
	return (EXIT_SUCCESS);
}
