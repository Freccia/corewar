/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/gui/keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/30 10:48:03 by lfabbro          ###   ########.fr       */
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
	else if (ch == KEY_UP && g_stepi < g_vm->cycle_to_die)
		g_stepi += 5;
	else if (ch == KEY_DOWN && g_stepi >= 10)
		g_stepi -= 5;
	else if (ch == KEY_DOWN && g_stepi > 1)
		--g_stepi;
	gui_stats(STATS_CYCLEL, g_cyclel);
	gui_stats(STATS_STEPI, g_stepi);
	return (YEP);
}

static int		onletter(int ch)
{
	if (ch == 's')
		return (g_running ? YEP : NOP);
	if (ch == 'o')
		vm_guiproc(g_vm->procs.head);
	else if (ch == 'p')
	{
		if (g_uiproc && g_uiproc->next)
			vm_guiproc(g_uiproc->next);
		else if (g_vm->procs.head)
			vm_guiproc(g_vm->procs.head);
	}
	return (YEP);
}

int				gui_onkey(int ch)
{
	t_keyh			*hook;
	static t_keyh	*keymap[KEY_MAX] = {
		[KEY_RIGHT] = onarrow,
		[KEY_LEFT] = onarrow,
		[KEY_UP] = onarrow,
		[KEY_DOWN] = onarrow,
		['s'] = onletter,
		['p'] = onletter,
		['o'] = onletter
	};

	if ((hook = keymap[ch]))
		return (hook(ch));
	return (YEP);
}
