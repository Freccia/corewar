/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:47 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/27 10:38:13 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "corewar.h"

int			cw_live(t_proc *proc, uint8_t *pc)
{
	int32_t		id;
	t_player	*player;

	pc = cw_move_ptr(pc, 1);
	id = cw_read_nbytes(pc, sizeof(id));
	proc->lastlive = g_cw->cycle;
	if ((player = vm_playersfind(&g_cw->players, id)))
	{
		player->lastlive = g_cw->cycle;
		if (g_cw->opt.v & 1)
			cw_verbose(proc, player->name, player->id, E_VALID_LIVE);
		proc->pc = cw_move_ptr(pc, 4);
		return (EXIT_SUCCESS);
	}
	if (g_cw->opt.v & 1)
		cw_verbose(proc, NULL, 0, E_INVALID_LIVE);
	proc->pc = cw_move_ptr(pc, 4);
	return (EXIT_SUCCESS);
}
