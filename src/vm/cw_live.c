/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:47 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/15 12:02:01 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_live(uint8_t *mem)
{
	int8_t		k;
	int			id;

	id = ft_mtoi(mem, 4);
	k = -1;
	while (++k < g_cw->n_champs)
		if (g_cw->champs[k].id == id)
			break ;
	if (!g_cw->champs[k].id)
		ft_printf("A live has been made... But nobody came.\n");
	else
	{
		g_cw->current->lastlive = g_cw->cycle;
		ft_printf("Player %s[%hhd] is alive!\n", g_cw->champs[k].name, k);
	}
	return (5);
}
