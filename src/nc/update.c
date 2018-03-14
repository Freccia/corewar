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

int			cw_nc_update(t_cw *cw)
{
	int ch;
	static int running = 0;

	if (!cw->opt.n)
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
			cw_nc_notify(cw, (uint16_t)ch, (uint16_t)(ch % 8), (uint8_t)ch);
		}
	}
	return (YEP);
}
