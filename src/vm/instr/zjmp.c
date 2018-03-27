/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:17:51 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/27 12:32:52 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_zjmp(t_proc *proc, uint8_t *pc)
{
	uint8_t		*ptr;
	uint16_t	addr;

	ptr = cw_move_ptr(pc, 1);
	addr = cw_read_nbytes(ptr, sizeof(uint16_t));
	if (proc->flags & _CW_CARRY)
		proc->pc = cw_move_ptr(proc->pc, addr);
	else
		proc->pc = cw_move_ptr(proc->pc, 3);
	return (EXIT_SUCCESS);
}
