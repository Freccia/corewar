/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:30:43 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/25 01:39:34 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "corewar.h"

static void		check_id(int r1)
{
	if (r1 > UINT16_MAX || r1 < 0)
	{
		errno = EOVERFLOW;
		cw_exit(EXIT_FAILURE, "%d: Invalid champion number: %m\n", r1);
	}
	if (vm_playersfind(&g_cw->players, r1))
		cw_exit(EXIT_FAILURE, "%d: Duplicate champion number\n", r1);
}

static int		init_procs(void)
{
	t_proc		proc;
	t_player	*champ;

	g_cw->cycle_to_die = CYCLE_TO_DIE;
	champ = g_cw->players.head;
	vm_guiinit();
	while (champ)
	{
		vm_procinit(&proc, champ);
		vm_procspush(&g_cw->procs, &proc);
		champ = champ->next;
	}
	return (YEP);
}

int				cw_vm_init(int ac, char **av, int r1)
{
	int			opt;
	int			id;
	t_player	player;

	id = 0;
	while (g_optind < ac)
	{
		if (g_cw->players.len >= MAX_PLAYERS)
			return (cw_exit(EXIT_FAILURE, "Too much players\n"));
		r1 = (r1) ? r1 : ++id;
		check_id(r1);
		vm_playerload(&player, av[g_optind], r1);
		vm_playerspush(&g_cw->players, &player);
		r1 = 0;
		if (++g_optind < ac)
		{
			if ((opt = ft_getopt(ac, av, "n:")) == WUT)
				r1 = 0;
			else if (opt != 'n')
				return (cw_exit(EXIT_FAILURE, NULL));
			else
				r1 = (uint16_t)ft_atoi(g_optarg);
		}
	}
	if (g_cw->players.len == 0)
		cw_exit(EXIT_FAILURE, "No players.\n");
	return (init_procs());
}
