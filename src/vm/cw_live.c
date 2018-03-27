/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:47 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/26 17:13:25 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "corewar.h"

int			cw_live(t_proc *proc, uint8_t *pc)
{
	int			id;
	uint8_t		mem[4];
	t_player	*champ;

	pc = cw_move_ptr(pc, 1);
	id = ft_mtoi(cw_map_mem(mem, pc, 4), 4);
	proc->lastlive = g_cw->cycle;
	if ((champ = vm_playersfind(&g_cw->players, id)))
	{
		champ->lastlive = g_cw->cycle;
		if (g_cw->opt.v & 1)
			cw_verbose(proc, champ->name, champ->id, E_VALID_LIVE);
		proc->pc = cw_move_ptr(pc, 4);
		return (EXIT_SUCCESS);
	}
	if (g_cw->opt.v & 1)
		cw_verbose(proc, NULL, 0, E_INVALID_LIVE);
	proc->pc = cw_move_ptr(pc, 4);
	return (EXIT_SUCCESS);
}
