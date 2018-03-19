/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:47 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/18 18:20:51 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_live(t_proc *proc, uint8_t *op_code)
{
	int			id;
	uint8_t		mem[4];
	t_champ		*champ;

	op_code = cw_move_ptr(op_code, 1);
	id = ft_mtoi(cw_map_mem(mem, op_code), 4);
	champ = g_cw->champs;
	while (champ)
	{
		if (champ->id == id)
		{
			proc->lastlive = g_cw->cycle;
			ft_printf("Player %s [%hd] is alive!\n", champ->name, champ->id);
			proc->pc = cw_move_ptr(op_code, 4);
			return (EXIT_SUCCESS);
		}
		champ = champ->next;
	}
	ft_printf("A live has been made... But nobody came.\n");
	proc->pc = cw_move_ptr(op_code, 4);
	return (EXIT_SUCCESS);
}
