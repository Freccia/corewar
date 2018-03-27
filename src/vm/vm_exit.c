/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:49:29 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/16 17:09:36 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_free(void)
{
	t_proc		*proc;
	t_player		*champ;
	void		*tmp;

	proc = g_cw->procs;
	while (proc)
	{
		tmp = proc->next;
		free(proc);
		proc = (t_proc *)tmp;
	}
	champ = g_cw->champs;
	while (champ)
	{
		tmp = champ->next;
		free(champ);
		champ = (t_player *)tmp;
	}
}

int				cw_exit(int ecode, char const *fmt, ...)
{
	va_list ap;

	if (g_cw)
	{
		cw_nc_exit();
		cw_free();
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
