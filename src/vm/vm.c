/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/vm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/13 20:00:19 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		print_usage(int ac, char **av)
{
	(void)ac;
	ft_printf("Usage: %s [ options ] <champ.cor> <...>\n", av[0]);
	ft_printf("	-c N    : Dumps memory after N execution cycles\n");
	ft_printf("	-v N    : Sets everbosity level to N (bitwise)\n");
	ft_printf("	-n      : Ncurses output mode\n");
	ft_printf("		- 0 : Essential\n");
	ft_printf("		- 1 : Lives\n");
	ft_printf("		- 2 : Cycles\n");
	ft_printf("...\n");
	return (EXIT_FAILURE);
}

int		cw_init(t_cw *cw)
{
	cw_nc_init(cw);
	return (YEP);
}

int		cw_exit(t_cw *cw)
{

	cw_nc_exit(cw);
	exit(EXIT_SUCCESS);
}

int		cw_run(t_cw *cw)
{
	while (1)
	{
		if (cw_nc_update(cw))
			return (cw_exit(cw));
		++cw->cycle;
	}
}

int 	main(int ac, char **av)
{
	int 	opt;
	t_cw	cw;

	g_optind = 1;
	if (ac < 2)
		return (print_usage(ac, av));
	ft_bzero(&cw, sizeof(t_cw));
	while ((opt = ft_getopt(ac, av, "nc:v:")) != -1)
	{
		if (opt == 'v')
			cw.opt.v = (uint8_t)ft_atoi(g_optarg);
		else if (opt == 'c')
			cw.opt.c = (uint8_t)ft_atoi(g_optarg);
		else if (opt == 'n')
			cw.opt.n ^= 1;
		else
			return (print_usage(ac, av));
	}
	if (!cw_init(&cw))
		cw_run(&cw);
	return (cw_exit(&cw));
}
