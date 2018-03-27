/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar/instr.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/26 17:15:36 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_INSTR_H
# define COREWAR_INSTR_H

# include "proc.h"

typedef int	(*t_instr)(t_proc *, uint8_t *);

int		vm_live(t_proc *proc, uint8_t *pc);
int		vm_opld(t_proc *proc, uint8_t *pc);
int		vm_st(t_proc *proc, uint8_t *pc);
int		vm_add(t_proc *proc, uint8_t *pc);
int		vm_sub(t_proc *proc, uint8_t *pc);
int		vm_and(t_proc *proc, uint8_t *pc);
int		vm_or(t_proc *proc, uint8_t *pc);
int		vm_xor(t_proc *proc, uint8_t *pc);
int		vm_zjmp(t_proc *proc, uint8_t *pc);
int		vm_ldi(t_proc *proc, uint8_t *pc);
int		vm_sti(t_proc *proc, uint8_t *pc);
int		vm_fork(t_proc *proc, uint8_t *pc);
int		vm_lld(t_proc *proc, uint8_t *pc);
int		vm_lldi(t_proc *proc, uint8_t *pc);
int		vm_lfork(t_proc *proc, uint8_t *pc);
int		vm_aff(t_proc *proc, uint8_t *pc);

#endif
