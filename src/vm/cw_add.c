/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:08:36 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/19 15:00:50 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_add(t_proc *proc, uint8_t *pc)
{
	uint8_t		*ptr;
	uint8_t		a[3];

	ptr = cw_move_ptr(pc, 2);
	a[0] = *ptr;
	ptr = cw_move_ptr(pc, 1);
	a[1] = *ptr;
	ptr = cw_move_ptr(pc, 1);
	a[2] = *ptr;
	if (a[0] == 0 || a[0] > REG_NUMBER || a[1] == 0 || a[1] > REG_NUMBER ||
		a[2] == 0 || a[2] > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[a[2]] = proc->reg[a[0]] + proc->reg[a[1]];
	cw_update_carry(proc, proc->reg[a[2]]);
	proc->pc = cw_move_ptr(pc, 5);
	return (EXIT_SUCCESS);
}
