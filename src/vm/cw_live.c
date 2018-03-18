/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:47 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/18 14:38:45 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_live(uint8_t *pc)
{
	int			id;
	uint8_t		mem[4];
	t_champ		*champ;

	pc = cw_move_ptr(pc, 1);
	id = ft_mtoi(cw_map_mem(mem, pc), 4);
	champ = g_cw->champs;
	while (champ)
	{
		if (champ->id == id)
		{
			g_cw->current->lastlive = g_cw->cycle;
			ft_printf("Player %s [%hd] is alive!\n", champ->name, champ->id);
			g_cw->current->pc = cw_move_ptr(pc, 4);
			return (EXIT_SUCCESS);
		}
		champ = champ->next;
	}
	ft_printf("A live has been made... But nobody came.\n");
	g_cw->current->pc = cw_move_ptr(pc, 4);
	return (EXIT_SUCCESS);
}
