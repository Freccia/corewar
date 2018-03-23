/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:09:10 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/23 17:07:30 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_aff(t_proc *proc, uint8_t *op_code)
{
	char		c;

	if (*(op_code = cw_move_ptr(op_code, 1)) == 0x40)
	{
		op_code = cw_move_ptr(op_code, 1);
		cw_update_carry(proc, (uint32_t)(c = *op_code % 256));
	}
	else
		return (EXIT_FAILURE);
	if (g_cw->opt.g & 4)
		ft_printf("Player %s [%hd] is saying something...\n \"%c\"",\
			g_cw->champs->name, g_cw->champs->id, c);
	return (EXIT_SUCCESS);
}
