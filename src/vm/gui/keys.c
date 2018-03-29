/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/gui/keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/12 18:15:53 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static int		onarrow(int ch)
{
	if (ch == KEY_RIGHT)
	{
		if (g_cyclel < 50)
			++g_cyclel;
		else if (g_cyclel >= 1000000 / 1.2)
			g_cyclel = 1000000;
		else if (g_cyclel < 1000000 / 1.2)
			g_cyclel *= 1.2;
	}
	else if (ch == KEY_LEFT)
	{
		if (g_cyclel > 1)
			g_cyclel < 50 ? (--g_cyclel) : ((g_cyclel /= 1.2));
	}
	else if (ch == KEY_UP && (size_t)g_stepi < g_vm->cycle_to_die)
		g_stepi += 5;
	else if (ch == KEY_DOWN && g_stepi >= 10)
		g_stepi -= 5;
	else if (ch == KEY_DOWN && g_stepi > 1)
		--g_stepi;
	cw_nc_stats(STATS_CYCLEL, g_cyclel);
	cw_nc_stats(STATS_STEPI, g_stepi);
	return (YEP);
}

static int		onnext(int ch)
{
	(void)ch;
	if (g_running)
		return (YEP);
	return (NOP);
}

static int		onp(int ch)
{
	(void)ch;
	if (!g_running)
	{
		if (g_uiproc && g_uiproc->next)
			vm_guiproc(g_uiproc->next);
		else if (g_vm->procs.head)
			vm_guiproc(g_vm->procs.head);
	}
	return (YEP);
}

static int		ono(int ch)
{
	(void)ch;
	if (!g_running)
	{
		if (g_vm->procs.head)
			vm_guiproc(g_vm->procs.head);
	}
	return (YEP);
}

static t_keyh	*g_keym[KEY_MAX] = {
	[KEY_RIGHT] = onarrow,
	[KEY_LEFT] = onarrow,
	[KEY_UP] = onarrow,
	[KEY_DOWN] = onarrow,
	['n'] = onnext,
	['s'] = onnext,
	['p'] = onp,
	['o'] = ono
};

int				cw_nc_onkey(int ch)
{
	t_keyh *hook;

	if ((hook = g_keym[ch]))
		return (hook(ch));
	return (YEP);
}
