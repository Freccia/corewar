/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 21:09:55 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/26 11:26:08 by lfabbro          ###   ########.fr       */
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

static int			cw_vm_check_arg(uint8_t op, uint8_t ocp, uint8_t n_arg)
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

static int			cw_vm_check_ocp(uint8_t *pc)
{
	uint8_t		ocp;

	ocp = *cw_move_ptr(pc, 1);
	if (cw_vm_check_arg((*pc - 1), ((ocp & 0xc0) >> 6), 0)
		|| cw_vm_check_arg((*pc - 1), ((ocp & 0x30) >> 4), 1)
		|| cw_vm_check_arg((*pc - 1), ((ocp & 0x0c) >> 2), 2))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int			cw_vm_proc_crash(t_proc *proc, uint16_t error)
{
	proc->crashed = error;
	return (EXIT_FAILURE);
}

int					cw_vm_exec(t_cw *cw, t_proc *proc, uint8_t *pc)
{
	if (*pc >= 0x1 && *pc <= MAX_OP && *pc == g_op_tab[*pc - 1].op_code)
	{
		if (!g_op_tab[*pc - 1].ocp || cw_vm_check_ocp(pc) == EXIT_SUCCESS)
		{
			cw_nc_notify(pc - cw->mem, cw->current->color, *pc);
			if (g_instr[*pc - 1](proc, pc))
				return (cw_vm_proc_crash(proc, E_WRONG_REG));
			cw_nc_notify(cw->current->pc - cw->mem,\
				cw->current->color + 5, *cw->current->pc);
			if (cw->opt.v & 4)
				cw_verbose(proc, g_cw->champs[proc->k]->name,\
						g_cw->champs[proc->k]->id, E_OP);
			return (EXIT_SUCCESS);
		}
		else
			return (cw_vm_proc_crash(proc, E_WRONG_OCP));
	}
	else
		return (cw_vm_proc_crash(proc, E_WRONG_OP));
	return (EXIT_FAILURE);
}
