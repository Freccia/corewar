/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:16:47 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/25 03:15:35 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_sti(t_proc *proc, uint8_t *pc)
{
	uint8_t		*ptr;
	uint8_t		*write;
	int32_t		a[2];
	uint32_t	reg;

	ptr = cw_move_ptr(pc, 2);
	reg = cw_read_arg(proc, &ptr, 0, F_REG_VAL);
	a[0] = cw_read_arg(proc, &ptr, 1, F_IND_RESTRICT | F_DIR | F_REG_VAL);
	a[1] = cw_read_arg(proc, &ptr, 2, F_DIR | F_REG_VAL);
	write = cw_move_ptr(pc, (a[0] + a[1]) % IDX_MOD);
	reg = swap_uint32(reg);
	cw_mem_cpy(write, (uint8_t*)&(reg), 4, proc->color + 2);
	cw_update_carry(proc, *write);
	proc->pc = cw_move_ptr(pc, ptr - pc);
	return (EXIT_SUCCESS);
}
