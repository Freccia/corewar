/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar/mem.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/26 17:15:36 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_MEM_H
# define COREWAR_MEM_H

# include "proc.h"

# define E_WRONG_OP		(-0x0a)
# define E_WRONG_OCP	(-0x0b)
# define E_WRONG_REG	(-0x0c)

# define F_DIR			1
# define F_DIR_LONG		2
# define F_IND			4
# define F_IND_RESTRICT	8
# define F_REG			16
# define F_REG_VAL		32

typedef	struct	s_args
{
	uint8_t		mask;
	uint8_t		shift;
}				t_args;

extern t_args	g_arg[MAX_ARGS_NUMBER + 1];

/*
** TODO: Doc
** @param pc
** @param len
** @return
*/
uint8_t *vm_move(uint8_t const *pc, int32_t len, uint8_t idx_mod);

/*
** TODO: Doc
** @param mem
** @param pc
** @param n
** @return
*/
uint8_t			*vm_map(uint8_t *mem, uint8_t *pc, uint16_t n);

/*
** TODO: Doc
** @param dst
** @param src
** @param len
** @param p
*/
void			vm_write(uint8_t *dst, uint8_t *src, size_t len, uint16_t p);

/*
** TODO: Doc
** @param proc
** @param value
*/
void			vm_carry(t_proc *proc, int32_t value);

/*
** TODO: Doc
** @param ptr
** @param n
** @return
*/
int32_t			vm_read(uint8_t *ptr, uint16_t n);

/*
** TODO: Doc
** @param pc
** @param ocp
** @param flags
** @return
*/
int32_t			vm_readref(uint8_t **pc, uint8_t *ocp, uint32_t flags);

/*
** TODO: Doc
** @param proc	Current process
** @param ptr	Pointer to the argument (it will be moved by size bytes)
** @param n		Number of the argument (g_arg[n])
** @param fl    Restricted address or not, direct or direct double, ...
** @return      The value of the argument on error, it returns 0
*/
int32_t			vm_readarg(t_proc *proc, uint8_t **ptr, uint8_t n, uint32_t fl);

#endif
