/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:17:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/29 11:21:42 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_instr	g_instr[MAX_OP] = {
	vm_live,
	vm_ld,
	vm_st,
	vm_add,
	vm_sub,
	vm_and,
	vm_or,
	vm_xor,
	vm_zjmp,
	vm_ldi,
	vm_sti,
	vm_fork,
	vm_lld,
	vm_lldi,
	vm_lfork,
	vm_aff,
	vm_gtmd
};

static int		check_arg(uint8_t op, uint8_t ocp, uint8_t n_arg)
{
	uint8_t arg_type;

	arg_type = g_op_tab[op].param_type[n_arg];
	if (arg_type == 0 && ocp == 0)
		return (EXIT_SUCCESS);
	else if ((arg_type & T_REG) && (ocp & REG_CODE))
		return (EXIT_SUCCESS);
	else if ((arg_type & T_DIR) && (ocp & DIR_CODE))
		return (EXIT_SUCCESS);
	else if ((arg_type & T_IND) && (ocp & IND_CODE))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static int		check_ocp(uint8_t *pc)
{
	uint8_t ocp;

	ocp = *vm_move(pc, 1, FALSE);
	if (check_arg((uint8_t)(*pc - 1), (uint8_t)((ocp & 0xc0) >> 6), 0))
		return (EXIT_FAILURE);
	if (check_arg((uint8_t)(*pc - 1), (uint8_t)((ocp & 0x30) >> 4), 1))
		return (EXIT_FAILURE);
	if (check_arg((uint8_t)(*pc - 1), (uint8_t)((ocp & 0x0c) >> 2), 2))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int				vm_eval(t_proc *proc, uint8_t *pc)
{
	int ret;

	ret = EXIT_FAILURE;
	if (*pc >= 0x1 && *pc <= MAX_OP)
	{
		if (g_op_tab[*pc - 1].ocp && check_ocp(pc) != EXIT_SUCCESS)
			proc->pc = vm_move(proc->pc, 2, FALSE);
		else
		{
			if (g_vm->opt.v & VM_VERB_OPERA && *pc >= 0x1 && *pc <= MAX_OP)
				ft_printf("Process %d [%s] executing %s\n", proc->pid,
					proc->owner->name, g_op_tab[*pc - 1].name);
			ret = g_instr[*pc - 1](proc, pc);
		}
	}
	if (g_vm->opt.v & VM_VERB_MOVES)
		ft_printf("Process %d [%s] PC moves by %td (%p -> %p)\n",
			proc->pid, proc->owner->name, proc->pc - pc, pc, proc->pc);
	return (ret);
}
