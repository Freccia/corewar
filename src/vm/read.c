/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 12:54:08 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/28 21:27:30 by nfinkel          ###   ########.fr       */
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

void		vm_carry(t_proc *proc, int32_t value)
{
	if (value)
		proc->carry = 0;
	else
		proc->carry = 1;
}

int32_t		vm_read(uint8_t *ptr, uint16_t n)
{
	uint8_t	mem[n + 1];

	if (n == sizeof(int16_t))
		return ((int32_t)(int16_t)ft_mtoi(vm_map(mem, ptr, n), n));
	return ((int32_t)ft_mtoi(vm_map(mem, ptr, n), n));
}

int32_t		vm_readref(uint8_t **ptr, uint8_t *pc, uint32_t flags)
{
	uint8_t		*pos;
	uint16_t	len;

	len = 2;
	if (flags & F_DIR || flags & F_DIR_LONG)
	{
		pos = *ptr;
		len = (uint16_t)((flags & F_DIR_LONG) ? 4 : 2);
	}
	else if (flags & F_IND_RESTRICT)
		pos = vm_move(pc, vm_read(*ptr, len), 1);
	else if (flags & F_IND)
		pos = vm_move(pc, vm_read(*ptr, len), 0);
	else
		return (0);
	*ptr = vm_move(*ptr, len, 0);
	return (vm_read(pos, len));
}

int32_t		vm_readarg(t_proc *proc, uint8_t **ptr, uint8_t n, uint32_t flags)
{
	uint8_t ocp;
	int32_t arg;
	uint8_t reg;

	ocp = (*vm_move(proc->pc, 1, 0) & g_arg[n].mask) >> g_arg[n].shift;
	arg = 0;
	if (ocp == REG_CODE)
	{
		reg = (uint8_t)**ptr;
		if (reg >= 0x1 && reg <= REG_NUMBER)
			arg = (flags & F_REG_VAL) ? proc->reg[reg] : reg;
		else
			proc->crashed = E_WRONG_REG;
		*ptr = vm_move(*ptr, 1, 0);
	}
	else if (ocp == DIR_CODE)
	{
		flags = (flags & F_DIR) | (flags & F_DIR_LONG);
		arg = vm_readref(ptr, proc->pc, flags);
	}
	else if (ocp == IND_CODE)
	{
		flags = (flags & F_IND) | (flags & F_IND_RESTRICT);
		arg = vm_readref(ptr, proc->pc, flags);
	}
	else
		proc->crashed = E_WRONG_OCP;
	return (arg);
}
