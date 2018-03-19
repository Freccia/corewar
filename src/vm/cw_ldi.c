/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:18 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/19 13:17:07 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// TODO terminate to write

int			cw_ldi(t_proc *proc, uint8_t *pc)
{
	uint8_t		*ptr;
	uint8_t		mem[4];
	uint32_t	a1;
	uint32_t	a2;
	uint8_t		reg;

	(void)proc;
	ptr = cw_move_ptr(pc, 2);
	a1 = cw_read_arg(pc, &ptr, 0, 2);
	a2 = cw_read_arg(pc, &ptr, 1, 2);
	ptr = cw_move_ptr(ptr, 1);
	reg = *ptr;

	ft_printf("opcode: %d\n", *pc);
	ft_printf("a1: %d	a2: %d		a3: %d\n", *pc, a1, a2, reg);

	// TODO is it correct?
	g_cw->current->reg[reg] = ft_mtoi(cw_map_mem(mem,
		cw_move_ptr(pc, a1 + a2)), 1);
	ft_printf("stored: %d\n", g_cw->current->reg[reg]);
	if (!g_cw->current->reg[reg])
		proc->flags |= _CW_CARRY;
	else
		proc->flags &= ~(_CW_CARRY);
	g_cw->current->pc = cw_move_ptr(ptr, pc - ptr);
	return (YEP);
}
