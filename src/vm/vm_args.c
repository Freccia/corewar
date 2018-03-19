/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 12:54:08 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/19 14:42:35 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cw_update_carry(t_proc *proc, uint32_t value)
{
	if (value)
		proc->flags |= _CW_CARRY;
	else
		proc->flags &= ~(_CW_CARRY);
}

t_args		g_args[MAX_ARGS_NUMBER + 1] = 
{
	{0xc0, 6},
	{0x30, 4},
	{0x0c, 2},
	{0x03, 0},
};

/*
**	cw_read_arg():
**
**	pc		-> program counter
**	ptr		-> pointer to the argument (it will be mooved by size octects)
**	n		-> number of the argument (g_args[n])
**	size	-> if (DIR || IND) it indicates the size of the argument
**
**	return: the value of the argument
*/

uint32_t	cw_read_arg(uint8_t *pc, uint8_t **ptr, uint8_t n, uint8_t size)
{
	uint8_t		ocp;
	uint32_t	arg;

	ocp = *cw_move_ptr(pc, 1);
	if ((ocp & g_args[n].mask) >> g_args[n].shift == REG_CODE)
	{
		arg = g_cw->current->reg[ft_mtoi(*ptr, 1)];
		*ptr = cw_move_ptr(*ptr, 1);
	}
	else if ((ocp & g_args[n].mask) >> g_args[n].shift == DIR_CODE)
		arg = cw_mem_read(ptr, pc, size, E_DIR);
	else if ((ocp & g_args[n].mask) >> g_args[n].shift == IND_CODE)
		arg = cw_mem_read(ptr, pc, size, E_IND_SHORT);
	else
		arg = 0;
	return (arg);
}
