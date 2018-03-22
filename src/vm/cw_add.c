/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:08:36 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/23 00:05:00 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_add(t_proc *proc, uint8_t *pc)
{
	uint8_t			*ptr;
	int32_t			a[3];

	ptr = cw_move_ptr(pc, 2);
	a[0] = cw_read_arg(proc, &ptr, 0, F_REG_VAL);
	a[1] = cw_read_arg(proc, &ptr, 1, F_REG_VAL);
	a[2] = cw_read_arg(proc, &ptr, 2, F_REG);
	if (a[2] == 0 || a[2] > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[a[2]] = a[0] + a[1];
	cw_update_carry(proc, proc->reg[a[2]]);
	proc->pc = cw_move_ptr(pc, 5);
	return (EXIT_SUCCESS);
}
