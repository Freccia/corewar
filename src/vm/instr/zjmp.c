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

	ptr = vm_move(pc, 1);
	addr = (uint16_t)vm_read(ptr, sizeof(uint16_t));
	if (proc->carry)
		proc->pc = vm_move(proc->pc, addr);
	else
		proc->pc = vm_move(proc->pc, 3);
	return (EXIT_SUCCESS);
}
