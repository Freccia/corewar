/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:16:47 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/21 19:11:12 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
void		cw_write(uint8_t *dst, uint32_t src)
{
	dst[0] = (src & 0xc0) >> 6;
	dst[1] = (src & 0x30) >> 4;
	dst[2] = (src & 0x0c) >> 2;
	dst[3] = (src & 0x03);
}
*/

int			cw_sti(t_proc *proc, uint8_t *pc)
{
	uint8_t		*ptr;
	uint32_t	*write;
	uint32_t	a[2];
	uint8_t		reg;

	ptr = cw_move_ptr(pc, 2);
	reg = cw_read_arg(proc, &ptr, 0, F_REG_VAL);
	a[0] = cw_read_arg(proc, &ptr, 1, F_IND_RESTRICT | F_DIR | F_REG_VAL);
	a[1] = cw_read_arg(proc, &ptr, 2, F_IND_RESTRICT | F_DIR);
	// TODO: %IDX_MOD ??
	write = (uint32_t*)cw_move_ptr(pc, (a[0] + a[1]) % IDX_MOD);
	*write = proc->reg[reg];
	cw_nc_notify(write - (uint32_t*)g_cw->mem, proc->color, *write);
	cw_update_carry(proc, *write);
	proc->pc = cw_move_ptr(pc, ptr - pc);
	return (EXIT_SUCCESS);
}
