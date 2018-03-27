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

# define VM_VERB_ESSEN (1 << 0)
# define VM_VERB_LIVES (1 << 1)
# define VM_VERB_CYCLE (1 << 2)
# define VM_VERB_OPERA (1 << 3)
# define VM_VERB_DEATH (1 << 4)
# define VM_VERB_MOVES (1 << 5)

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

typedef struct		s_opt
{
	uint8_t			v;
	ssize_t			d;
	uint8_t			g : 1;
	uint16_t		ctmo;
}					t_opt;

typedef struct		s_cw
{
	uint8_t			mem[MEM_SIZE];
	t_opt			opt;
	size_t			cycle;
	size_t			cycle_to_die;
	t_players		players;
	t_procs			procs;
}					t_cw;

typedef int			(*t_instr)(t_proc *, uint8_t *);

extern t_cw			*g_cw;
extern t_args		g_arg[MAX_ARGS_NUMBER + 1];

int					cw_live(t_proc *proc, uint8_t *pc);
int					cw_ld(t_proc *proc, uint8_t *pc);
int					cw_st(t_proc *proc, uint8_t *pc);
int					cw_add(t_proc *proc, uint8_t *pc);
int					cw_sub(t_proc *proc, uint8_t *pc);
int					cw_and(t_proc *proc, uint8_t *pc);
int					cw_or(t_proc *proc, uint8_t *pc);
int					cw_xor(t_proc *proc, uint8_t *pc);
int					cw_zjmp(t_proc *proc, uint8_t *pc);
int					cw_ldi(t_proc *proc, uint8_t *pc);
int					cw_sti(t_proc *proc, uint8_t *pc);
int					cw_fork(t_proc *proc, uint8_t *pc);
int					cw_lld(t_proc *proc, uint8_t *pc);
int					cw_lldi(t_proc *proc, uint8_t *pc);
int					cw_lfork(t_proc *proc, uint8_t *pc);
int					cw_aff(t_proc *proc, uint8_t *pc);

int					cw_nc_init(void);
int					cw_nc_update(void);
int					cw_nc_notify(uint16_t i, uint16_t c, uint8_t val);
int					cw_nc_exit(void);

t_player				*cw_find_champ(t_cw *cw, int32_t id);
void				cw_mem_dump(uint8_t *mem);
void				cw_mem_cpy(uint8_t *dst, uint8_t *src, size_t len,
						uint16_t p);
uint8_t				*cw_map_mem(uint8_t *mem, uint8_t *pc, uint16_t n);
uint8_t				*cw_move_ptr(uint8_t const *pc, int32_t len);
int32_t				cw_read_mem(uint8_t **pc, uint8_t *ocp, uint32_t flags);
int32_t				cw_read_nbytes(uint8_t *ptr, uint16_t n);
int32_t				cw_read_arg(t_proc *proc, uint8_t **ptr, uint8_t n,
						uint32_t flags);
char				*cw_get_opcode_name(uint8_t op);
void				cw_update_carry(t_proc *proc, int32_t value);
void				cw_verbose(const t_proc *proc, const char *name, int id,
						t_verbose flag);

/*
** parse instruction arguments
** return the pc offset or -1 in case of zboub (error)
*/
void				cw_vm_eval(t_proc *proc);

/*
** parse fichier cor
*/
void				cw_vm_insert_sort(t_player **head);
int					cw_vm_init(int ac, char **av, int r1);
int					cw_vm_run(void);
int					cw_exit(int ecode, char const *fmt, ...);

/*
** init vm opt
*/
int		cw_vm_usage(int ac, char **av);
int		cw_vm_check_ctmo(int ctmo);
int		cw_vm_parse_opt(int ac, char **av, t_cw *cw);


#endif
