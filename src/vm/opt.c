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
	"Usage: %s [ options ] <champ.cor> <...>\n"\
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

static uint8_t		verboselvl(void)
{
	int v;

	if ((v = ft_atoi(g_optarg)) < 0 && errno)
		vm_exit(EXIT_FAILURE, "%c: %m\n", 'v');
	if (v < 0 || v > 0xff)
		vm_exit(EXIT_FAILURE, "%c: %d: Must be positive\n", 'v', v);
	return ((uint8_t)v);
}

int					vm_optparse(t_opt *vm, int ac, char **av)
{
	int 	opt;
	int 	r1;

	if (ac < 2)
		vm_exit(EXIT_FAILURE, g_usage, av[0]);
	g_optind = 1;
	r1 = 0;
	while ((opt = ft_getopt(ac, av, "gd:v:n:c:")) != -1)
	{
		if (opt == 'v')
			vm->v = verboselvl();
		else if (opt == 'd')
			vm->d = ft_atoi(g_optarg);
		else if (opt == 'g')
			vm->g ^= 1;
		else if (opt == 'c')
			vm->ctmo = (uint16_t)ft_atoi(g_optarg);
		else if (opt == 'n')
		{
			r1 = (int)ft_atoi(g_optarg);
			break ;
		}
		else
			return (ft_printf("%s\n", g_usage));
	}
	return (r1);
}
