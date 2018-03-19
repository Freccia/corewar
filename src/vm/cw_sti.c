/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:16:47 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/19 17:56:30 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_sti(t_proc *proc, uint8_t *pc)
{
	uint8_t		*ptr;
	uint32_t	*write;
	uint32_t	a[2];
	uint8_t		reg;

	ptr = cw_move_ptr(pc, 2);
	reg = *ptr;
	ptr = cw_move_ptr(pc, 1);
	a[0] = cw_read_arg(proc, &ptr, 0, E_IND_SHORT);
	a[1] = cw_read_arg(proc, &ptr, 1, E_IND_SHORT);
	if (!reg || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	// TODO: %IDX_MOD ??
	write = (uint32_t*)cw_move_ptr(pc, (a[0] + a[1]) % IDX_MOD);
	*write = proc->reg[reg];
	cw_update_carry(proc, *write);
	proc->pc = cw_move_ptr(pc, 8);
	return (EXIT_SUCCESS);
}
