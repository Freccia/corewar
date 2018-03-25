/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:18 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/25 20:47:58 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_ldi(t_proc *proc, uint8_t *op_code)
{
	uint8_t			reg;
	uint8_t			mem[4];
	uint8_t			*ptr;
	uint8_t			*read;
	uint32_t		a[2];

	ptr = cw_move_ptr(op_code, 2);
	a[0] = cw_read_arg(proc, &ptr, 0, F_IND_RESTRICT | F_DIR | F_REG_VAL);
	a[1] = cw_read_arg(proc, &ptr, 1, F_IND_RESTRICT | F_DIR);
	reg = cw_read_arg(proc, &ptr, 2, F_REG);
	if (!reg || reg > REG_NUMBER || proc->kill == TRUE)
		return (-1);
	read = cw_move_ptr(op_code, (a[0] + a[1]) % IDX_MOD);
	proc->reg[reg] = ft_mtoi(cw_map_mem(mem, read, sizeof(mem)), 1);
	cw_update_carry(proc, proc->reg[reg]);
	proc->pc = cw_move_ptr(op_code, ptr - op_code);
	return (0);
}
