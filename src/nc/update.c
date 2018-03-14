/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nc/update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/12 18:15:53 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"
/*
static int	g_stats[10][2] = {

};*/

static void	nc_pause(int *running)
{
	int ch;

	*running = 0;
	while ((ch = getch()) != 32)
	{
		if (ch == 27)
			cw_exit(EXIT_SUCCESS, "Good bye!\n");
	}
	*running = 1;
}

static int	nc_stats(void)
{
	return (YEP);
}

int			cw_nc_update()
{
	int ch;
	static int running = 0;

	if (!g_cw->opt.n)
		return (YEP);
	if (!running)
		nc_pause(&running);
	if ((ch = getch()) != ERR)
	{
		if (ch == 27)
			return (cw_exit(EXIT_SUCCESS, "Good bye!\n"));
		else if (ch == 32)
			nc_pause(&running);
		else
		{
			ft_printf("got %d\n", ch);
		}
	}
	nc_stats();
	return (YEP);
}
