/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:47 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/26 11:06:31 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_live(t_proc *proc, uint8_t *pc)
{
	int32_t		id;
	int			k;
	t_champ		*champ;

	pc = cw_move_ptr(pc, 1);
	id = cw_read_nbytes(pc, sizeof(id));
	proc->lastlive = g_cw->cycle;
	k = -1;
	while (++k < g_cw->n_champs && (champ = g_cw->champs[k]))
		if (champ->id == id)
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
