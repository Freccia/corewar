/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/gui/cell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/12 18:15:53 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

int	gui_cellattrs(t_cell *cell)
{
	int a;

	if (cell->attrs & GUI_BOLD)
		wattr_on(g_wboard, A_BOLD, NULL);
	if (cell->attrs & GUI_NOCOLOR)
		a = COLOR_PAIR(0);
	else if (cell->attrs & GUI_INV)
		a = COLOR_PAIR(cell->color + GUI_COLOR_INV);
	else if (cell->attrs & GUI_HINT)
		a = COLOR_PAIR(cell->color + GUI_COLOR_HINT);
	else
		a = COLOR_PAIR(cell->color);
	if (cell->lifetime > 0)
	{
		if (!--cell->lifetime)
		{
			cell->attrs = 0;
			cell->print = 0;
		}
	}
	return (a);
}
