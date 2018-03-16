/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:47 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/15 17:55:57 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_live(uint8_t *pc)
{
	int8_t		k;
	int			id;
	uint8_t		mem[4];

	id = ft_mtoi(cw_map_mem(mem, pc), 4);
	k = -1;
	while (++k < g_cw->n_champs)
		if (g_cw->champs[k].id == id)
		{
			g_cw->current->lastlive = g_cw->cycle;
			ft_printf("Player %s [%hhd] is alive!\n", g_cw->champs[k].name, k);
			g_cw->current->pc = cw_move_pc(pc, 4);
			return (EXIT_SUCCESS);
		}
	ft_printf("A live has been made... But nobody came.\n");
	g_cw->current->pc = cw_move_pc(pc, 4);
	return (EXIT_SUCCESS);
}
