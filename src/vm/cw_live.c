/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:47 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/23 18:16:12 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "corewar.h"

int			cw_live(t_proc *proc, uint8_t *op_code)
{
	int			id;
	uint8_t		mem[4];
	t_champ		*champ;

	op_code = cw_move_ptr(op_code, 1);
	id = ft_mtoi(cw_map_mem(mem, op_code, 4), 4);
	proc->lastlive = g_cw->cycle;
	champ = g_cw->champs;
	while (champ)
	{
		if (champ->id == id)
		{
			champ->lastlive = g_cw->cycle;
			if (g_cw->opt.v & 1)
				cw_verbose(proc, champ->name, champ->id, E_VALID_LIVE);
			proc->pc = cw_move_ptr(op_code, 4);
			return (EXIT_SUCCESS);
		}
		champ = champ->next;
	}
	if (g_cw->opt.v & 1)
		cw_verbose(proc, NULL, 0, E_INVALID_LIVE);
	proc->pc = cw_move_ptr(op_code, 4);
	return (EXIT_SUCCESS);
}
