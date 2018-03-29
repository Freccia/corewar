/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:55:56 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/27 22:12:39 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static const char	*g_usage =
{
	"Usage: %s [ options ] <[-n <champ.id>] champ.cor> <...>\n"\
	"	-d N    : Dumps memory after N execution cycles\n"\
	"	-g      : Ncurses GUI\n"\
	"	-c N    : CTMO - Cycles till memory opens\n"\
	"	-v N    : Sets verbosity level to N (bitwise)\n"\
	"		- 0 : Show essentials\n"\
	"		- 1 : Show lives\n"\
	"		- 2 : Show cycles\n"\
	"		- 4 : Show operations\n"\
	"		- 8 : Show deaths\n"\
	"		-16 : Show PC movement\n"\
};

static uint8_t		verb(void)
{
	int v;

	if ((v = ft_atoi(g_optarg)) < 0 && errno)
		vm_exit(EXIT_FAILURE, "%c: %m\n", 'v');
	if ((v & ~VM_VERB))
		vm_exit(EXIT_FAILURE, "%c: %d: Invalid verbose level\n", 'v', v);
	return ((uint8_t)v);
}

static uint16_t		ctmo(void)
{
	int ctmo;

	if ((ctmo = ft_atoi(g_optarg)) < 0 && errno)
		vm_exit(EXIT_FAILURE, "%c: %m\n", 'c');
	if (ctmo < 0 || ctmo > UINT16_MAX)
		vm_exit(EXIT_FAILURE, "%c: %d: Invalid ctmo argument\n", 'c', ctmo);
	return ((uint16_t)ctmo);
}

static uint32_t		dump(void)
{
	int d;

	if ((d = ft_atoi(g_optarg)) < 0 && errno)
		vm_exit(EXIT_FAILURE, "%c: %m\n", 'c');
	if (d < 0 || d > UINT32_MAX)
		vm_exit(EXIT_FAILURE, "%c: %d: Invalid dump argument\n", 'd', d);
	return ((uint32_t)d);
}

void				vm_optparse(t_opt *vm, int ac, char **av)
{
	int opt;

	if (ac < 2)
		vm_exit(EXIT_FAILURE, g_usage, av[0]);
	g_optind = 1;
	while (!errno && (opt = ft_getopt(ac, av, "gd:v:n:c:")) != WUT)
		if (opt == 'v')
			vm->v = verb();
		else if (opt == 'd')
			vm->d = dump();
		else if (opt == 'g')
			vm->g ^= 1;
		else if (opt == 'c')
			vm->ctmo = ctmo();
		else if (opt == 'n')
		{
			g_optind -= 2;
			break ;
		}
		else
			vm_exit(EXIT_FAILURE, g_usage, av[0]);
	if (errno)
		vm_exit(EXIT_FAILURE, "%s: %m\n", av[g_optind]);
}
