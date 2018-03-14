/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nc/notify.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/12 18:15:53 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

int	cw_nc_notify(uint16_t i, uint16_t c, uint8_t val)
{
	int sq;
	int x;
	int y;

	if (!g_cw->opt.n)
		return (YEP);
	sq = getmaxy(g_wboard) - 2;
	x = 2 + ((i % sq) * 3);
	y = 1 + (i / sq);
	mvwaddch(g_wboard, y, x++, (chtype)DIGITS[(val / 16) % 16] | COLOR_PAIR(c));
	mvwaddch(g_wboard, y, x++, (chtype)DIGITS[val % 16] | COLOR_PAIR(c));
	mvwaddch(g_wboard, y, x++, ' ');
	wrefresh(g_wboard);
	return (YEP);
}
