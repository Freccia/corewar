/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/15 12:42:06 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_cw		*g_cw = NULL;

t_instr		g_instr[16] =
{
	cw_live,
	cw_ld,
	cw_st,
	cw_add,
	cw_sub,
	cw_and,
	cw_or,
	cw_xor,
	cw_zjmp,
	cw_ldi,
	cw_sti,
	cw_fork,
	cw_lld,
	cw_lldi,
	cw_lfork,
	cw_aff
};	

static int	cw_vm_usage(int ac, char **av)
{
	(void)ac;
	ft_printf("Usage: %s [ options ] <champ.cor> <...>\n", av[0]);
	ft_printf("	-d N    : Dumps memory after N execution cycles\n");
	ft_printf("	-v N    : Sets verbosity level to N (bitwise)\n");
	ft_printf("	-g      : Ncurses GUI\n");
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
		cw_nc_exit();
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

int		cw_vm_kill_process(t_proc **proc, t_proc *prev)
{
	if ((*proc)->next != NULL && prev != *proc)
		prev->next = (*proc)->next;
	if (*proc == g_cw->procs)
		g_cw->procs = (*proc)->next;
	free(*proc);
	*proc = NULL;
	return (EXIT_SUCCESS);
}

int		cw_vm_exec(uint8_t *pc)
{
	if (*pc >= 0x1 && *pc <= 0x10)
		return(g_instr[*pc](g_cw->current->pc));
	return (EXIT_FAILURE);
}

int		cw_vm_eval(t_proc *proc)
{
	t_instr		instr;
	int16_t		ocp;

	(void)instr;
	if (!proc)
		return (EXIT_SUCCESS);
	if (proc->wait > 0)
	{
		--proc->wait;
		return (EXIT_SUCCESS);
	}
	if ((ocp = cw_vm_exec(proc->pc)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	proc->pc += ocp % MEM_SIZE;
	//proc->wait = cw_instr_cycles(*proc->pc);
	proc->wait = g_op_tab[*proc->pc][4];
	return (EXIT_SUCCESS);
}

int		cw_vm_run(void)
{
	while (g_cw->cycle_to_die > 0)
	{
		if (cw_nc_update())
			return (cw_exit(EXIT_FAILURE, NULL));
		++g_cw->cycle;
		if (g_cw->opt.d > 0 && g_cw->cycle == (size_t)g_cw->opt.d)
		{
			// todo: dump mem
			return (cw_exit(EXIT_SUCCESS, NULL));
		}
		if (cw_vm_eval(g_cw->current) == EXIT_FAILURE)
			cw_vm_kill_process(&g_cw->current, g_cw->prev);
		if (g_cw->cycle >= (size_t)g_cw->cycle_to_die)
		{
			g_cw->cycle = 0;
			g_cw->cycle_to_die -= CYCLE_DELTA;
		}
		g_cw->prev = g_cw->current;
		if (g_cw->current && (g_cw->current = g_cw->current->next) == NULL)
			g_cw->current = g_cw->procs;
	}
	return (EXIT_SUCCESS);
}

int 	main(int ac, char **av)
{
	int 	opt;
	t_cw	cw;
	int		n;

	g_optind = 1;
	if (ac < 2)
		return (cw_vm_usage(ac, av));
	ft_bzero(&cw, sizeof(t_cw));
	n = 1;
	while ((opt = ft_getopt(ac, av, "gd:v:n:")) != -1)
	{
		if (opt == 'v')
			cw.opt.v = (uint8_t)ft_atoi(g_optarg);
		else if (opt == 'd')
			cw.opt.d = ft_atoi(g_optarg);
		else if (opt == 'g')
			cw.opt.g ^= 1;
		else if (opt == 'n')
		{
			n = (int)ft_atoi(g_optarg);
			break ;
		}
		else
			return (cw_vm_usage(ac, av));
	}
	g_cw = &cw;
	if (cw_vm_init(ac, av, n))
		return (cw_exit(EXIT_FAILURE, NULL));
	if (cw_vm_run())
		return (cw_exit(EXIT_FAILURE, NULL));
	return (cw_exit(EXIT_SUCCESS, NULL));
}
