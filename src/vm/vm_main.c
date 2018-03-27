/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/26 16:29:30 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_vm		*g_vm;

static const char		*g_usage =
{
	"Usage: corewar [ options ] <champ.cor> <...>\n"\
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
	"..."
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

static int			cw_vm_parse_opt(int ac, char **av, t_vm *cw)
{
	int 	opt;
	int 	r1;

	g_optind = 1;
	r1 = 0;
	while ((opt = ft_getopt(ac, av, "gd:v:n:c:")) != -1)
	{
		if (opt == 'v')
			cw->opt.v = verboselvl();
		else if (opt == 'd')
			cw->opt.d = ft_atoi(g_optarg);
		else if (opt == 'g')
			cw->opt.g ^= 1;
		else if (opt == 'c')
			cw->opt.ctmo = (uint16_t)ft_atoi(g_optarg);
		else if (opt == 'n')
		{
			r1 = (int)ft_atoi(g_optarg);
			break ;
		}
		else
			return (ft_printf("%s\n", g_usage));
	}
	g_vm = cw;
	return (r1);
}

int 	main(int ac, char **av)
{
	t_vm	cw;
	int		r1;

	if (ac < 2)
		return (ft_printf("%s\n", g_usage));
	ft_bzero(&cw, sizeof(t_vm));
	r1 = cw_vm_parse_opt(ac, av, &cw);
	if (vm_init(ac, av, r1))
		return (vm_exit(EXIT_FAILURE, NULL));
	if (vm_run())
		return (vm_exit(EXIT_FAILURE, NULL));
	return (vm_exit(EXIT_SUCCESS, NULL));
}
