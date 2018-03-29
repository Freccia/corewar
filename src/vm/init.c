/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:30:43 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/28 21:07:22 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		check_id(int r1)
{
	if (errno || r1 > INT32_MAX || r1 < INT32_MIN)
	{
		if (!errno)
			errno = EOVERFLOW;
		vm_exit(EXIT_FAILURE, "%d: %m\n", r1);
	}
	if (vm_playersfind(&g_vm->players, r1))
		vm_exit(EXIT_FAILURE, "%d: Duplicate champion number\n", r1);
}

static int		init_procs(void)
{
	t_proc		proc;
	t_player	*champ;

	if (g_vm->players.len == 0)
		vm_exit(EXIT_FAILURE, "No players.\n");
	ft_printf("Introducing contestants...\n");
	g_vm->cycle_to_die = CYCLE_TO_DIE;
	champ = g_vm->players.head;
	vm_guiinit();
	while (champ)
	{
		ft_printf("* Player %hhu, weighing %lu bytes, \"%s\" (\"%s\") !\n",
			champ->idx + 1, champ->size, champ->name, "COMMENT PLACEHOLDER"); //TODO put comment here
		vm_procinit(&proc, champ);
		vm_procspush(&g_vm->procs, &proc);
		champ = champ->next;
	}
	return (YEP);
}

int				vm_init(int ac, char **av)
{
	int			opt;
	int			id;
	int			r1;
	t_player	player;

	id = 0;
	while (g_optind < ac)
	{
		if (g_vm->players.len >= MAX_PLAYERS)
			vm_exit(EXIT_FAILURE, "Too much players\n");
		r1 = --id;
		if (g_optind < ac)
		{
			if ((opt = ft_getopt(ac, av, "n:")) != WUT && opt != 'n')
				vm_exit(EXIT_FAILURE, NULL);
			opt == 'n' ? check_id(r1 = ft_atoi(g_optarg)) : 0;
			if (opt == 'n' && g_optind >= ac)
				vm_exit(EXIT_FAILURE, "n: Missing champion after option\n");
		}
		vm_playerload(&player, av[g_optind++], r1);
		vm_playerspush(&g_vm->players, &player);
	}
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
	}
	if (fmt)
	{
		if (isatty(STDERR_FILENO))
			ft_fprintf(g_stderr, CLR_RED"corewar: "CLR_RESET);
		else
			ft_fprintf(g_stderr, "corewar: ");
		va_start(ap, fmt);
		ft_vfprintf(g_stderr, fmt, ap);
		va_end(ap);
	}
	exit(ecode);
}
