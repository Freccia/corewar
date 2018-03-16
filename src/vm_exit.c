/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:49:29 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/16 16:52:35 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		cw_free(void)
{
	t_proc		*proc;
	t_champ		*champ;
	void		*tmp;

	while (proc)
	{
		tmp = proc->next;
		free(proc);
		proc = (t_proc *)tmp;
	}
	while (champ)
	{
		tmp = champ->next;
		free(champ);
		champ = (t_champ *)tmp;
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
