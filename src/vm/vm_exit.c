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

int	cw_exit(int ecode, char const *fmt, ...)
{
	va_list ap;

	if (g_cw)
	{
		cw_nc_exit();
		vm_playersclr(&g_cw->players);
		vm_procsclr(&g_cw->procs);
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
