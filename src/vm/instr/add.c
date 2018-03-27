/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:08:36 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/27 10:27:21 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_add(t_proc *proc, uint8_t *pc)
{
	uint8_t *ptr;
	int32_t av[3];

	ptr = cw_move_ptr(pc, 2);
	av[0] = cw_read_arg(proc, &ptr, 0, F_REG_VAL);
	av[1] = cw_read_arg(proc, &ptr, 1, F_REG_VAL);
	av[2] = cw_read_arg(proc, &ptr, 2, F_REG);
	if (av[2] < 0x1 || av[2] > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[av[2]] = av[0] + av[1];
	cw_update_carry(proc, proc->reg[av[2]]);
	proc->pc = cw_move_ptr(pc, 5);
	if (g_vm->opt.v & VM_VERB_OPERA)
	{
		ft_printf("[OPERA] add: [%d, %d, %d] %d\n",
			av[0], av[1], av[2], proc->reg[av[2]]);
	}
	return (EXIT_SUCCESS);
}
