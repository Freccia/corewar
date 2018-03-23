/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:17:51 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/23 18:13:20 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_zjmp(t_proc *proc, uint8_t *op_code)
{
	uint8_t		*ptr;
	uint32_t	addr;

	ptr = cw_move_ptr(op_code, 1);
	addr = cw_read_arg(proc, &ptr, 0, F_DIR);
	if (proc->flags & _CW_CARRY)
		proc->pc = cw_move_ptr(proc->pc, addr);
	else
		proc->pc = cw_move_ptr(proc->pc, 3);
	return (EXIT_SUCCESS);
}
