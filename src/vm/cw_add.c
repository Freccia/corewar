/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:08:36 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/26 18:06:47 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_add(t_proc *proc, uint8_t *pc)
{
	uint8_t *it;
	int32_t av[3];

	it = cw_move_ptr(pc, 2);
	av[0] = cw_read_arg(proc, &it, 0, F_REG_VAL);
	av[1] = cw_read_arg(proc, &it, 1, F_REG_VAL);
	av[2] = cw_read_arg(proc, &it, 2, F_REG);
	if (av[2] <= 0 || av[2] > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[av[2]] = av[0] + av[1];
	cw_update_carry(proc, proc->reg[av[2]]);
	proc->pc = cw_move_ptr(pc, 5);
	if (g_cw->opt.v & VM_VERB_OPERA)
	{
		ft_printf("[OPERA] add: [%d, %d, %d] %d\n",
			av[0], av[1], av[2], proc->reg[av[2]]);
	}
	return (EXIT_SUCCESS);
}
