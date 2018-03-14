/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:07:52 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/14 19:08:03 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** OP: 0xb	-- instruction len: 8
*/

int					cw_sti(uint8_t a1, uint8_t a2, uint8_t a3)
{
	(void)a2;
	(void)a3;
	if (a1 < 1 || a1 > REG_NUMBER)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
