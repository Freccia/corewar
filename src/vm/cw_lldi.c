/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:13:09 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/19 20:21:36 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_lldi(t_proc *proc, uint8_t *pc)
{
	uint8_t		*ptr;
	uint8_t		*read;
	uint8_t		mem[4];
	uint32_t	a[2];
	uint8_t		reg;

	ptr = cw_move_ptr(pc, 2);
	a[0] = cw_read_arg(proc, &ptr, 0, E_IND_LONG);
	a[1] = cw_read_arg(proc, &ptr, 1, E_IND_LONG);
	ptr = cw_move_ptr(ptr, 1);
	reg = *ptr;
	if (!reg || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	read = cw_move_ptr(pc, a[0] + a[1]);
	proc->reg[reg] = ft_mtoi(cw_map_mem(mem, read), 1);
	cw_update_carry(proc, g_cw->current->reg[reg]);
	proc->pc = cw_move_ptr(pc, 8);
	return (EXIT_SUCCESS);
}
