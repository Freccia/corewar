/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:17:51 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/27 22:00:13 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_zjmp(t_proc *proc, uint8_t *pc)
{
	uint8_t	*ptr;
	int16_t	addr;

	ptr = vm_move(pc, 1, 0);
	addr = (int16_t)vm_read(ptr, sizeof(int16_t));
	if (proc->carry)
		proc->pc = vm_move(proc->pc, addr, 0);
	else
		proc->pc = vm_move(proc->pc, 3, 0);
	return (EXIT_SUCCESS);
}
