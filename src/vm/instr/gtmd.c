/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtmd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 18:51:18 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/28 21:28:56 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			vm_gtmd(t_proc *proc, uint8_t *pc)
{
	int8_t reg;

	pc = vm_move(pc, 2, FALSE);
	reg = (int8_t)vm_readarg(proc, &pc, 0, F_REG);
	proc->pc = pc;
	if (reg < 1 || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	proc->reg[reg] = (int32_t)g_vm->opt.ctmo;
	return (EXIT_SUCCESS);
}
