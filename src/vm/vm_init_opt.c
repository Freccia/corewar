/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mc.maxcanal@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 19:47:22 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/23 17:48:32 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_cw		*g_cw;

int		cw_vm_usage(int ac, char **av)
{
	(void)ac;
	ft_printf("Usage: %s [ options ] <champ.cor> <...>\n", av[0]);
	ft_printf("	-d N    : Dumps memory after N execution cycles\n");
	ft_printf("	-g      : Ncurses GUI\n");
	ft_printf("	-c N    : CTMO - Cycles till memory opens\n");
	ft_printf("	-v N    : Sets verbosity level to N (bitwise)\n");
	ft_printf("		- 0 : Show essentials\n");
	ft_printf("		- 1 : Show lives\n");
	ft_printf("		- 2 : Show cycles\n");
	ft_printf("		- 4 : Show operations\n");
	ft_printf("		- 8 : Show deaths\n");
	ft_printf("		-16 : Show PC movement\n");
	ft_printf("...\n");
	return (EXIT_FAILURE);
}

int		cw_vm_check_ctmo(int ctmo)
{
	return (ctmo <= 0 ? 0 : ctmo);
}

int		cw_vm_parse_opt(int ac, char **av, t_cw *cw)
{
	int 	opt;
	int 	r1;

	g_optind = 1;
	r1 = 0;
	while ((opt = ft_getopt(ac, av, "gd:v:n:c:")) != -1)
	{
		if (opt == 'v')
			cw->opt.v = (uint8_t)ft_atoi(g_optarg);
		else if (opt == 'd')
			cw->opt.d = ft_atoi(g_optarg);
		else if (opt == 'g')
			cw->opt.g ^= 1;
		else if (opt == 'c')
			cw->opt.ctmo = cw_vm_check_ctmo(ft_atoi(g_optarg));
		else if (opt == 'n')
		{
			r1 = (int)ft_atoi(g_optarg);
			break ;
		}
		else
			return (cw_vm_usage(ac, av));
	}
	g_cw = cw;
	return (r1);
}
