/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/vm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/14 11:54:38 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_cw	*g_cw = NULL;

static int	cw_vm_usage(int ac, char **av)
{
	(void)ac;
	ft_printf("Usage: %s [ options ] <champ.cor> <...>\n", av[0]);
	ft_printf("	-d N    : Dumps memory after N execution cycles\n");
	ft_printf("	-v N    : Sets verbosity level to N (bitwise)\n");
	ft_printf("	-n      : Ncurses output mode\n");
	ft_printf("		- 0 : Essential\n");
	ft_printf("		- 1 : Lives\n");
	ft_printf("		- 2 : Cycles\n");
	ft_printf("...\n");
	return (EXIT_FAILURE);
}

int		cw_exit(int ecode, char const *fmt, ...)
{
	va_list ap;

	if (g_cw)
	{
		cw_nc_exit(g_cw);
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

int		cw_vm_run(t_cw *cw)
{
	(void)cw;
	while (1)
	{
		if (cw_nc_update(cw))
			return (cw_exit(EXIT_FAILURE, NULL));
		if (cw->opt.d && ++cw->cycle == cw->opt.d)
		{
			// todo: dump mem
			return (cw_exit(EXIT_SUCCESS, NULL));
		}
	}
}

int 	main(int ac, char **av)
{
	int 	opt;
	t_cw	cw;

	g_optind = 1;
	if (ac < 2)
		return (cw_vm_usage(ac, av));
	ft_bzero(&cw, sizeof(t_cw));
	if ((opt = ft_getopt(ac, av, "nd:v:")) != -1)
	{
		if (opt == 'v')
			cw.opt.v = (uint8_t)ft_atoi(g_optarg);
		else if (opt == 'd')
			cw.opt.d = ft_atoi(g_optarg);
		else if (opt == 'n')
			cw.opt.n ^= 1;
		else
			return (cw_vm_usage(ac, av));
	}
	if (cw_vm_init(g_cw = &cw, ac, av))
		return (cw_exit(EXIT_FAILURE, NULL));
	if (cw_vm_run(&cw))
		return (cw_exit(EXIT_FAILURE, NULL));
	return (cw_exit(EXIT_SUCCESS, NULL));
}
