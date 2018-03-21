/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:47 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/21 20:40:45 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_live(t_proc *proc, uint8_t *pc)
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
			//proc->lastlive = g_cw->cycle;
			champ->lastlive = g_cw->cycle;
			ft_printf("Player %s [%hd] is alive!\n", champ->name, champ->id);
			proc->pc = cw_move_ptr(pc, 4);
			return (EXIT_SUCCESS);
		}
		champ = champ->next;
	}
	ft_printf("A live has been made... But nobody came.\n");
	proc->pc = cw_move_ptr(pc, 4);
	return (EXIT_SUCCESS);
}
