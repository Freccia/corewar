/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/27 10:28:58 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <libft.h>

# include "cw_common.h"
# include "op.h"

#include "corewar/gui.h"
#include "corewar/instr.h"
#include "corewar/mem.h"
#include "corewar/player.h"
#include "corewar/proc.h"
#include "corewar/vm.h"

# define _CW_CARRY		(1 << 0)
# define _CW_HEAD_SZ	(16 + PROG_NAME_LENGTH + COMMENT_LENGTH)

// TODO do not use those, but g_args in cw_args.c
# define MASK_ARG2 (0x30)
# define MASK_ARG3 (0x0c)

# define E_WRONG_OP		(-0x0a)
# define E_WRONG_OCP	(-0x0b)
# define E_WRONG_REG	(-0x0c)

# define F_DIR			1
# define F_DIR_LONG		2
# define F_IND			4
# define F_IND_RESTRICT	8
# define F_REG			16
# define F_REG_VAL		32

typedef enum		e_verbose
{
	E_INVALID_LIVE,
	E_VALID_LIVE,
	E_CYCLE,
	E_DELTA,
	E_OP,
	E_DEATH,
	E_MOVE
}					t_verbose;

typedef	struct		s_args
{
	uint8_t			mask;
	uint8_t			shift;
}					t_args;

extern t_args		g_arg[MAX_ARGS_NUMBER + 1];

void				cw_mem_dump(uint8_t *mem);
void				cw_mem_cpy(uint8_t *dst, uint8_t *src, size_t len, uint16_t p);
uint8_t				*cw_map_mem(uint8_t *mem, uint8_t *pc, uint16_t n);
uint8_t				*cw_move_ptr(uint8_t const *pc, int32_t len);
int32_t				cw_read_mem(uint8_t **pc, uint8_t *ocp, uint32_t flags);
int32_t				cw_read_nbytes(uint8_t *ptr, uint16_t n);
int32_t				cw_read_arg(t_proc *proc, uint8_t **ptr, uint8_t n, uint32_t flags);
void				cw_update_carry(t_proc *proc, int32_t value);

#endif
