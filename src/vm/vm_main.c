/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/25 21:50:13 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_cw					*g_cw;

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

static int			parse_opt(int ac, char **av, t_opt *opt)
{
	int		n;
	int		r1;

	g_optind = 1;
	r1 = 0;
	while ((n = ft_getopt(ac, av, "gd:v:n:c:")) != -1)
	{
		if (n == 'v')
			opt->v = (uint8_t)ft_atoi(g_optarg);
		else if (n == 'd')
			opt->d = ft_atoi(g_optarg);
		else if (n == 'g')
			opt->g ^= 1;
		else if (n == 'c')
			opt->ctmo = ft_atoi(g_optarg);
		else if (n == 'n')
		{
			r1 = (int)ft_atoi(g_optarg);
			break ;
		}
		else
			return (-1);
	}
	opt->ctmo = (opt->ctmo < 1 ? 0 : opt->ctmo);
	return (r1);
}

int					main(int ac, char **av)
{
	t_cw		cw;
	int			r1;

	g_cw = &cw;
	ft_memset(g_cw, '\0', sizeof(t_cw));
	if (ac == 1 || (r1 = parse_opt(ac, av, &cw.opt) == -1))
	{
		ft_printf("%s\n", g_usage);
		return (EXIT_SUCCESS);
	}
	cw_vm_init(ac, av, r1);
	cw_vm_run(g_cw);
	return (cw_exit(EXIT_SUCCESS, NULL));
}
