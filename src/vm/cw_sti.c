/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:16:47 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/21 20:46:47 by lfabbro          ###   ########.fr       */
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
	uint8_t		*write;
	int32_t		a[2];
	uint32_t	reg;

	ptr = cw_move_ptr(pc, 2);
	reg = cw_read_arg(proc, &ptr, 0, F_REG_VAL);
	a[0] = (int32_t)cw_read_arg(proc, &ptr, 1, F_IND_RESTRICT | F_DIR | F_REG_VAL);
	a[1] = (int32_t)cw_read_arg(proc, &ptr, 2, F_IND_RESTRICT | F_DIR);
	//ft_printf("reg: %d	a1: %d	a2: %d\n", reg, a[0], a[1]);
	//ft_printf("move: %d\n", (a[0] + a[1]) % IDX_MOD);
	// TODO: %IDX_MOD ??
	write = cw_move_ptr(pc, (a[0] + a[1]) % IDX_MOD);
	reg = swap_uint32(reg);
	cw_mem_cpy(write, (uint8_t*)&(reg), 4, proc->color);
	cw_update_carry(proc, *write);
	proc->pc = cw_move_ptr(pc, ptr - pc);
	return (EXIT_SUCCESS);
}
