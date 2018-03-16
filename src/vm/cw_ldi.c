/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:18 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/16 20:12:36 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// TODO terminate to write

int			cw_ldi(uint8_t *mem)
{
	uint8_t		*ocp;
	uint8_t		mem[4];
	uint32_t	a1;
	uint32_t	a2;
	uint8_t		reg;

	ocp = mem;
	if ((*ocp & 0xc0) >> 6 | T_REG)
		a1 = g_cw->current->reg[ft_mtoi(cw_move_ptr(mem, 1))];
	else if ((*ocp & 0xc0) >> 6 | T_DIR)
		a1 = cw_mem_read_dir(&mem, 4, 2, E_SHORT);
	else if ((*ocp & 0xc0) >> 6 | T_IND)
		a1 = cw_mem_read_ind(&mem, 4, 2, E_SHORT);

	if ((*ocp & 0x30) >> 4 | T_REG)
		a2 = ft_mtoi(cw_move_ptr(mem, 1));
	else if ((*ocp & 0x30) >> 4 | T_DIR)
		a2 = cw_mem_read_dir(&mem, 4, 1, E_SHORT);

	reg = ft_mtoi(cw_map_mem(mem, mem), 1);


	g_cw->current->pc = cw_move_ptr(ocp, mem - ocp);
	return (YEP);
}
