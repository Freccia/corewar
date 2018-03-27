/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:09:10 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/25 03:11:23 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_aff(t_proc *proc, uint8_t *pc)
{
	char		c;

	if (*(pc = cw_move_ptr(pc, 1)) == 0x40)
	{
		pc = cw_move_ptr(pc, 1);
		cw_update_carry(proc, (uint32_t)(c = *pc % 256));
	}
	else
		return (EXIT_FAILURE);
	if (g_vm->opt.g & 4)
		ft_printf("Player %s [%hd] is saying something...\n \"%c\"",\
			proc->owner->name, proc->owner->id, c);
	return (EXIT_SUCCESS);
}
