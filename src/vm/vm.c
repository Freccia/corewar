/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/20 11:36:12 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_cw		*g_cw;

static int	cw_vm_usage(int ac, char **av)
{
	ft_printf("Usage: %s [ options ] <champ.cor> <...>\n", av[0]);
	ft_printf("	-d N    : Dumps memory after N execution cycles\n");
	ft_printf("	-g      : Ncurses GUI\n");
	ft_printf("	-c N    : CTMO - Cycles till memory opens\n");
	ft_printf("	-v N    : Sets verbosity level to N (bitwise)\n");
	ft_printf("		- 0 : Essential\n");
	ft_printf("		- 1 : Lives\n");
	ft_printf("		- 2 : Cycles\n");
	ft_printf("...\n");
	return (EXIT_FAILURE);
}

int		cw_vm_check_ctmo(int ctmo)
{
	return (ctmo <= 0 ? 0 : ctmo);
}

int 	main(int ac, char **av)
{
	int 	opt;
	t_cw	cw;
	int		r1;

	g_optind = 1;
	if (ac < 2)
		return (cw_vm_usage(ac, av));
	ft_bzero(&cw, sizeof(t_cw));
	r1 = 1;
	while ((opt = ft_getopt(ac, av, "gd:v:n:c:")) != -1)
	{
		if (opt == 'v')
			cw.opt.v = (uint8_t)ft_atoi(g_optarg);
		else if (opt == 'd')
			cw.opt.d = ft_atoi(g_optarg);
		else if (opt == 'g')
			cw.opt.g ^= 1;
		else if (opt == 'c')
			cw.opt.ctmo = cw_vm_check_ctmo(ft_atoi(g_optarg));
		else if (opt == 'n')
		{
			r1 = (int)ft_atoi(g_optarg);
			break ;
		}
		else
			return (cw_vm_usage(ac, av));
	}
	g_cw = &cw;
	if (cw_vm_init(ac, av, r1))
		return (cw_exit(EXIT_FAILURE, NULL));
	if (cw_vm_run())
		return (cw_exit(EXIT_FAILURE, NULL));
	return (cw_exit(EXIT_SUCCESS, NULL));
}
