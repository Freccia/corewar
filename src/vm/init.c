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
		vm_exit(EXIT_FAILURE, "%d: Invalid champion number: %m\n", r1);
	}
	if (vm_playersfind(&g_vm->players, r1))
		vm_exit(EXIT_FAILURE, "%d: Duplicate champion number\n", r1);
}

static int		init_procs(void)
{
	t_proc		proc;
	t_player	*champ;

	g_vm->cycle_to_die = CYCLE_TO_DIE;
	champ = g_vm->players.head;
	vm_guiinit();
	while (champ)
	{
		vm_procinit(&proc, champ);
		vm_procspush(&g_vm->procs, &proc);
		champ = champ->next;
	}
	return (YEP);
}

int				vm_init(int ac, char **av, int r1)
{
	int			opt;
	int			id;
	t_player	player;

	id = 0;
	while (g_optind < ac)
	{
		if (g_vm->players.len >= MAX_PLAYERS)
			return (vm_exit(EXIT_FAILURE, "Too much players\n"));
		r1 = (r1) ? r1 : ++id;
		check_id(r1);
		vm_playerload(&player, av[g_optind], r1);
		vm_playerspush(&g_vm->players, &player);
		r1 = 0;
		if (++g_optind < ac)
		{
			if ((opt = ft_getopt(ac, av, "n:")) == WUT)
				r1 = 0;
			else if (opt != 'n')
				return (vm_exit(EXIT_FAILURE, NULL));
			else
				r1 = (uint16_t)ft_atoi(g_optarg);
		}
	}
	if (g_vm->players.len == 0)
		vm_exit(EXIT_FAILURE, "No players.\n");
	return (init_procs());
}

int				vm_exit(int ecode, char const *fmt, ...)
{
	va_list ap;

	if (g_vm)
	{
		vm_guiexit();
		vm_playersclr(&g_vm->players);
		vm_procsclr(&g_vm->procs);
		// todo: destruct things
	}
	if (fmt)
	{
		ft_fprintf(g_stderr, "corewar: ");
		va_start(ap, fmt);
		ft_vfprintf(g_stderr, fmt, ap);
		va_end(ap);
	}
	exit(ecode);
}
