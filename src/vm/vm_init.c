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

static int		cw_vm_check_r1(int r1)
{
	if (r1 > UINT16_MAX || r1 < 0)
	{
		errno = EOVERFLOW;
		cw_exit(EXIT_FAILURE, "%d: Invalid champion number: %m\n", r1);
	}
	if (vm_playersfind(&g_cw->players, r1))
		cw_exit(EXIT_FAILURE, "%d: Duplicate champion number\n", r1);
	return (r1);
}

static int		cw_vm_load_champs(uint8_t i)
{
	int		plyrs_dist;
	t_proc	*ptr;
	t_player	*champ;

	plyrs_dist = (int)(MEM_SIZE / g_cw->players.len);
	g_cw->cycle_to_die = CYCLE_TO_DIE;
	champ = g_cw->players.head;
	cw_nc_init();
	while (champ)
	{
		if (!(ptr = malloc(sizeof(t_proc))))
			return (cw_exit(EXIT_FAILURE, "%m\n"));
		ft_bzero(ptr, sizeof(t_proc));
		ptr->owner = champ;
		ptr->pc = g_cw->mem + (i * plyrs_dist);
		ptr->pid = ++g_cw->max_pid;
		ptr->reg[1] = champ->id;
		cw_mem_cpy(ptr->pc, champ->bin, champ->size,
			(uint16_t)(ptr->owner->idx + CW_GUI_COLOR_DFT));
		ptr->wait = g_op_tab[*ptr->pc - 1].cycles;
		++g_cw->proc_count;
		g_cw->procs ? (ptr->next = g_cw->procs) : 0;
		g_cw->procs = ptr;
		champ = champ->next;
		++i;
	}
	g_cw->prev = g_cw->procs;
	g_cw->current = g_cw->procs;
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
		r1 = cw_vm_check_r1(r1);
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
	return (cw_vm_load_champs(0));
}
