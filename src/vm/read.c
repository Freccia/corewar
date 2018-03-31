/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 12:54:08 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/31 17:38:31 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_args		g_arg[MAX_ARGS_NUMBER + 1] = {
	{0xc0, 6},
	{0x30, 4},
	{0x0c, 2},
	{0x03, 0},
};

void			vm_carry(t_proc *proc, int32_t value)
{
	if (value)
		proc->carry = 0;
	else
		proc->carry = 1;
}

int32_t			vm_read(uint8_t *ptr, uint16_t n)
{
	uint8_t	mem[n + 1];

	if (n == sizeof(int16_t))
		return ((int32_t)(int16_t)ft_mtoi(vm_map(mem, ptr, n), n));
	return ((int32_t)ft_mtoi(vm_map(mem, ptr, n), n));
}

static int32_t	readref(uint8_t **ptr, uint8_t *pc, uint32_t flags)
{
	uint8_t		*pos;
	uint16_t	len;
	uint16_t	move;

	len = sizeof(int16_t);
	move = len;
	if (flags & F_DIR || flags & F_DIR_LONG)
	{
		pos = *ptr;
		len = (uint16_t)((flags & F_DIR_LONG) ?
				sizeof(int32_t) : sizeof(int16_t));
		move = len;
	}
	else if ((flags & F_IND) || (flags & F_IND_RESTRICT))
	{
		pos = vm_move(pc, vm_read(*ptr, move), flags & F_IND_RESTRICT);
		len = sizeof(int32_t);
	}
	else
		return (0);
	*ptr = vm_move(*ptr, move, FALSE);
	return (vm_read(pos, len));
}

int32_t			vm_readarg(t_proc *proc, uint8_t **ptr, uint8_t n, uint32_t fl)
{
	uint8_t ocp;
	int32_t arg;
	uint8_t reg;

	ocp = (*vm_move(proc->pc, 1, FALSE) & g_arg[n].mask) >> g_arg[n].shift;
	arg = 0;
	if (ocp == REG_CODE)
	{
		reg = (uint8_t)**ptr;
		if (reg >= 0x1 && reg <= REG_NUMBER)
			arg = (fl & F_REG_VAL) ? proc->reg[reg] : reg;
		else
			proc->state = STATE_DYING;
		*ptr = vm_move(*ptr, 1, FALSE);
	}
	else if (ocp == DIR_CODE)
		arg = readref(ptr, proc->pc, (fl & F_DIR) | (fl & F_DIR_LONG));
	else if (ocp == IND_CODE)
		arg = readref(ptr, proc->pc, (fl & F_IND) | (fl & F_IND_RESTRICT));
	else
		proc->state = STATE_DYING;
	return (arg);
}
