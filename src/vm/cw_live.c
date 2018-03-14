/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:01:10 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/14 18:46:52 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** OP: 0x1	-- instruction len: 5
*/

int					cw_live(uint8_t a1, uint8_t a2, uint8_t a3)
{
	t_proc	*ptr;

	(void)a2;
	(void)a3;
	ptr = g_cw->procs;
	while (ptr)
	{
		if (ptr->color == a1)
		{
			ptr->lastlive = g_cw->cycle;
			ft_printf("Player %d (%s) is alive!\n", ptr->color,
				g_cw->players[ptr->color - 1]);
			break ;
		}
		ptr = ptr->next;
	}
	if (ptr == NULL)
		ft_printf("A non-existent player (%d) is telling he's alive...", a1);
	return (EXIT_SUCCESS);
}
