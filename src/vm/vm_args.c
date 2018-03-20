/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 12:54:08 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/20 11:25:34 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_args		g_args[MAX_ARGS_NUMBER + 1] = 
{
	{0xc0, 6},
	{0x30, 4},
	{0x0c, 2},
	{0x03, 0},
};

void		cw_update_carry(t_proc *proc, uint32_t value)
{
	if (value)
		proc->flags |= _CW_CARRY;
	else
		proc->flags &= ~(_CW_CARRY);
}

/*
**	uint32_t	cw_read_arg()
**
**	proc	-> current process
**	pc		-> program counter
**	ptr		-> pointer to the argument (it will be mooved by size octects)
**	n		-> number of the argument (g_args[n])
**	size	-> if DIR it indicates the size of the argument
**	flags	-> restricted address or not
**
**	return: the value of the argument
**			on error, it returns 0
*/

uint32_t	cw_read_arg(t_proc *proc, uint8_t **ptr, uint8_t n, uint8_t flags)
{
	uint8_t		ocp;
	uint32_t	arg;
	uint8_t		reg;
	uint8_t		size;

	ocp = (*cw_move_ptr(proc->pc, 1) & g_args[n].mask) >> g_args[n].shift;
	size = (g_op_tab[*(proc->pc)].direct_size) ? 4 : 2;
	arg = 0;
	if (ocp == REG_CODE)
	{
		reg = ft_mtoi(*ptr, 1);
		if (reg != 0 && reg < REG_NUMBER)
			arg = proc->reg[reg];
		else
			proc->crashed = E_WRONG_REG;
		*ptr = cw_move_ptr(*ptr, 1);
	}
	else if (ocp == DIR_CODE)
		arg = cw_mem_read(ptr, proc->pc, size, E_DIR);
	else if (ocp == IND_CODE)
		arg = cw_mem_read(ptr, proc->pc, 2, flags);
	else
		proc->crashed = E_WRONG_OCP;
	return (arg);
}
