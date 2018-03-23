/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:16:47 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/23 18:12:49 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_sti(t_proc *proc, uint8_t *op_code)
{
	uint8_t		*ptr;
	uint8_t		*write;
	int32_t		a[2];
	uint32_t	reg;

	ptr = cw_move_ptr(op_code, 2);
	reg = cw_read_arg(proc, &ptr, 0, F_REG_VAL);
	a[0] = (int32_t)cw_read_arg(proc, &ptr, 1, F_IND_RESTRICT | F_DIR | F_REG_VAL);
	a[1] = (int32_t)cw_read_arg(proc, &ptr, 2, F_IND_RESTRICT | F_DIR);
	write = cw_move_ptr(op_code, (a[0] + a[1]) % IDX_MOD);
	reg = swap_uint32(reg);
	cw_mem_cpy(write, (uint8_t*)&(reg), 4, proc->color + 2);
	cw_update_carry(proc, *write);
	proc->pc = cw_move_ptr(op_code, ptr - op_code);
	return (EXIT_SUCCESS);
}
