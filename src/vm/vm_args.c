/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 12:54:08 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/27 12:46:30 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_args		g_arg[MAX_ARGS_NUMBER + 1] = 
{
	{0xc0, 6},
	{0x30, 4},
	{0x0c, 2},
	{0x03, 0},
};

char		*cw_get_opcode_name(uint8_t op)
{
	if (op >= 0x1 && op <= MAX_OP)
		return (g_op_tab[op - 1].name);
	return (NULL);
}

void		cw_update_carry(t_proc *proc, int32_t value)
{
	if (value)
		proc->flags &= ~(_CW_CARRY);
	else
		proc->flags |= _CW_CARRY;
}

int32_t		cw_read_mem(uint8_t **ptr, uint8_t *pc, uint32_t flags)
{
	uint8_t		*pos;
	size_t		len;

	len = 2;
	if (flags & F_DIR || flags & F_DIR_LONG)
	{
		pos = *ptr;
		len = (flags & F_DIR_LONG) ? 4 : 2;
	}
	else if (flags & F_IND_RESTRICT)
		pos = cw_move_ptr(pc, cw_read_nbytes(*ptr, len));// % IDX_MOD);
	else if (flags & F_IND)
		pos = cw_move_ptr(pc, cw_read_nbytes(*ptr, len));
	else
		return (0);
	*ptr = cw_move_ptr(*ptr, len);
	return (cw_read_nbytes(pos, len));
}

/*
**	uint32_t	cw_read_arg()
**
**	proc	-> current process
**	ptr		-> pointer to the argument (it will be mooved by size octects)
**	n		-> number of the argument (g_arg[n])
**	flags	-> restricted address or not, direct or direct double, ...
**
**	return: the value of the argument
**			on error, it returns 0
*/

int32_t		cw_read_arg(t_proc *proc, uint8_t **ptr, uint8_t n, uint32_t flags)
{
	uint8_t		ocp;
	uint32_t	arg;
	uint8_t		reg;

	ocp = (*cw_move_ptr(proc->pc, 1) & g_arg[n].mask) >> g_arg[n].shift;
	arg = 0;
	if (ocp == REG_CODE)
	{
		reg = (uint8_t)**ptr;
		if (reg >= 0x1 && reg <= REG_NUMBER)
			arg = (flags & F_REG_VAL) ? proc->reg[reg] : reg;
		else
			proc->crashed = E_WRONG_REG;
		*ptr = cw_move_ptr(*ptr, 1);
	}
	else if (ocp == DIR_CODE)
	{
		flags = (flags & F_DIR) | (flags & F_DIR_LONG);
		arg = cw_read_mem(ptr, proc->pc, flags);
	}
	else if (ocp == IND_CODE)
	{
		flags = (flags & F_IND) | (flags & F_IND_RESTRICT);
		arg = cw_read_mem(ptr, proc->pc, flags);
	}
	else
		proc->crashed = E_WRONG_OCP;
	return (arg);
}
