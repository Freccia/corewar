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
	ft_printf("	-c N	: Dumps memory after N execution cycles\n");
	ft_printf("	-v N	: Sets everbosity level to N (bitwise)\n");
	ft_printf("		- 0 : Essential\n");
	ft_printf("		- 1 : Lives\n");
	ft_printf("		- 2 : Cycles\n");
	ft_printf("...\n");
	return (EXIT_FAILURE);
}

int		cw_init(t_cw *cw)
{
	memset(cw, 0, sizeof(t_cw));
	return (EXIT_SUCCESS);
}

int		cw_run(t_cw *cw)
{
	(void)cw;
	return (WUT);
}

int 	main(int ac, char **av)
{
	int 	opt;
	t_cw	cw;

	g_optind = 1;
	if (ac < 2)
		return (print_usage(ac, av));
	cw_init(&cw);
	while ((opt = ft_getopt(ac, av, "c:v:")) != -1)
	{
		if (opt == 'v')
			cw.opt.v = (uint8_t)ft_atoi(g_optarg);
		else if (opt == 'c')
			cw.opt.c = (uint8_t)ft_atoi(g_optarg);
		else
			return (EXIT_FAILURE);
	}
	cw_run(&cw);
	return (EXIT_SUCCESS);
}
