/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/28 18:52:12 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_INSTR_H
# define COREWAR_INSTR_H

# include "proc.h"

typedef int	(*t_instr)(t_proc *, uint8_t *);

/*
** TODO: Doc
** @param proc The proc which ask for operation.
** @param pc   The proc pointer.
** @return     0 If the operation succeed, 1 otherwise.   
*/
int		vm_live(t_proc *proc, uint8_t *pc);

/*
** TODO: Doc
** @param proc The proc which ask for operation.
** @param pc   The proc pointer.
** @return     0 If the operation succeed, 1 otherwise.  
*/
int		vm_ld(t_proc *proc, uint8_t *pc);

/*
** TODO: Doc
** @param proc The proc which ask for operation.
** @param pc   The proc pointer.
** @return     0 If the operation succeed, 1 otherwise.  
*/
int		vm_st(t_proc *proc, uint8_t *pc);

/*
** TODO: Doc
** @param proc The proc which ask for operation.
** @param pc   The proc pointer.
** @return     0 If the operation succeed, 1 otherwise.  
*/
int		vm_add(t_proc *proc, uint8_t *pc);

/*
** TODO: Doc
** @param proc The proc which ask for operation.
** @param pc   The proc pointer.
** @return     0 If the operation succeed, 1 otherwise.  
*/
int		vm_sub(t_proc *proc, uint8_t *pc);

/*
** TODO: Doc
** @param proc The proc which ask for operation.
** @param pc   The proc pointer.
** @return     0 If the operation succeed, 1 otherwise.  
*/
int		vm_and(t_proc *proc, uint8_t *pc);

/*
** TODO: Doc
** @param proc The proc which ask for operation.
** @param pc   The proc pointer.
** @return     0 If the operation succeed, 1 otherwise.  
*/
int		vm_or(t_proc *proc, uint8_t *pc);

/*
** TODO: Doc
** @param proc The proc which ask for operation.
** @param pc   The proc pointer.
** @return     0 If the operation succeed, 1 otherwise.  
*/
int		vm_xor(t_proc *proc, uint8_t *pc);

/*
** TODO: Doc
** @param proc The proc which ask for operation.
** @param pc   The proc pointer.
** @return     0 If the operation succeed, 1 otherwise.  
*/
int		vm_zjmp(t_proc *proc, uint8_t *pc);

/*
** TODO: Doc
** @param proc The proc which ask for operation.
** @param pc   The proc pointer.
** @return     0 If the operation succeed, 1 otherwise.  
*/
int		vm_ldi(t_proc *proc, uint8_t *pc);

/*
** Take a registry, and two indexes (potentially registries) add the two
** indexes, and use this result as an address where the value of the first
** parameter will be copied.
** @param proc The proc which ask for operation.
** @param pc   The proc pointer.
** @return     0 If the operation succeed, 1 otherwise.  
*/
int		vm_sti(t_proc *proc, uint8_t *pc);

/*
** There is no argument’s coding byte, take an index, opcode 0x0c. Create a new
** process that will inherit the different states of its father, except its PC,
** which will be put at (PC + (1st parameter % IDX_MOD))
** @param proc The proc which ask for operation.
** @param pc   The proc pointer.
** @return     0 If the operation succeed, 1 otherwise.  
*/
int		vm_fork(t_proc *proc, uint8_t *pc);

/*
** Means long-load, so it’s opcode is obviously 13.  It the same as ld, but
** without % IDX_MOD. Modify the carry.
** @param proc The proc which ask for operation.
** @param pc   The proc pointer.
** @return     0 If the operation succeed, 1 otherwise.  
*/
int		vm_lld(t_proc *proc, uint8_t *pc);

/*
** TODO: Doc
** @param proc The proc which ask for operation.
** @param pc   The proc pointer.
** @return     0 If the operation succeed, 1 otherwise.  
*/
int		vm_lldi(t_proc *proc, uint8_t *pc);

/*
** Means long-fork, to be able to fork abut straw from a distance of 15 meters,
** exactly like with its opcode. Same as a fork without modulo in the address.
** @param proc The proc which ask for operation.
** @param pc   The proc pointer.
** @return     0 If the operation succeed, 1 otherwise.  
*/
int		vm_lfork(t_proc *proc, uint8_t *pc);

/*
** TODO: Doc
** @param proc The proc which ask for operation.
** @param pc   The proc pointer.
** @return     0 If the operation succeed, 1 otherwise.  
*/
int		vm_aff(t_proc *proc, uint8_t *pc);

/*
** TODO: Doc
** @param proc The proc which ask for operation.
** @param pc   The proc pointer.
** @return     0 If the operation succeed, 1 otherwise.  
*/
int		vm_gtmd(t_proc *proc, uint8_t *pc);

/*
** Eval the operation which the pc point to.
** @param proc The proc which ask for operation.
** @param pc   The proc pointer.
** @return     The result of the operation or 1 if not an operation.
*/
int		vm_eval(t_proc *proc, uint8_t *pc);

#endif
