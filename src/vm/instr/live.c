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

int			vm_live(t_proc *proc, uint8_t *pc)
{
	int32_t		id;
	t_player	*player;

	vm_guinotify((uint16_t)(proc->pc - g_vm->mem), -1, GUI_HINT, 50);
	pc = vm_move(pc, 1, FALSE);
	id = vm_read(pc, sizeof(id));
	proc->lastlive = g_vm->cycle_total;
	if ((player = vm_playersfind(&g_vm->players, id)))
	{
		player->lastlive = (uint32_t)g_vm->cycle_total;
		if (g_vm->opt.v & VM_VERB_LIVES)
			ft_printf("Player %s [%hd] is alive!\n", player->name, player->id);
		proc->pc = vm_move(pc, 4, FALSE);
		return (EXIT_SUCCESS);
	}
	if (g_vm->opt.v & VM_VERB_LIVES)
		ft_printf("Process %d [%s] made a live... But nobody came.\n",
			proc->pid, proc->owner->name);
	proc->pc = vm_move(pc, 4, FALSE);
	return (EXIT_SUCCESS);
}
