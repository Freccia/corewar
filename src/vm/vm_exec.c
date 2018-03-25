/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 21:09:55 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/25 21:09:56 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_instr		g_instr[MAX_OP]=
{
	cw_live,
	cw_ld,
	cw_st,
	cw_add,
	cw_sub,
	cw_and,
	cw_or,
	cw_xor,
	cw_zjmp,
	cw_ldi,
	cw_sti,
	cw_fork,
	cw_lld,
	cw_lldi,
	cw_lfork,
	cw_aff
};

static int			check_arg(uint8_t op, uint8_t ocp, uint8_t n_arg)
{
	uint8_t		arg_type;

	arg_type = g_op_tab[op].param_type[n_arg];
	if (!arg_type && !ocp)
		return (EXIT_SUCCESS);
	else if ((arg_type & T_REG) && (ocp & REG_CODE))
		return (EXIT_SUCCESS);
	else if ((arg_type & T_DIR) && (ocp & DIR_CODE))
		return (EXIT_SUCCESS);
	else if ((arg_type & T_IND) && (ocp & IND_CODE))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static int			check_ocp(uint8_t *pc, uint8_t *ocp)
{
	if (check_arg((*pc - 1), ((*ocp & 0xc0) >> 6), 0)
		|| check_arg((*pc - 1), ((*ocp & 0x30) >> 4), 1)
		|| check_arg((*pc - 1), ((*ocp & 0x0c) >> 2), 2))
		return (-1);
	return (0);
}

int					cw_vm_exec(t_proc *proc, uint8_t *pc)
{
	if (!g_op_tab[*pc - 1].ocp || !check_ocp(pc, cw_move_ptr(pc, 1)))
	{
		cw_nc_notify(pc - g_cw->mem, g_cw->current->color, *pc);
		if (g_instr[*pc - 1](proc, pc))
			return (-1);
		cw_nc_notify(g_cw->current->pc - g_cw->mem,\
			g_cw->current->color + 5, *g_cw->current->pc);
		if (g_cw->opt.v & 4)
			cw_verbose(proc, "PUT CHAMP NAME", 0, E_OP);
		return (0);
	}
	else
		return (-1);
}
