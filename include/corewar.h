/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/20 11:26:24 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <libft.h>

# include "cw_common.h"
# include "op.h"

# define _CW_CARRY		(1 << 0)
# define _CW_HEAD_SZ	(16 + PROG_NAME_LENGTH + COMMENT_LENGTH)

// TODO do not use those, but g_args
# define MASK_ARG2 (0x30)
# define MASK_ARG3 (0x0c)

# define E_WRONG_OP		(-0x0a)
# define E_WRONG_OCP	(-0x0b)
# define E_WRONG_REG	(-0x0c)

typedef enum		e_flag
{
	E_DIR,
	E_IND_LONG,
	E_IND_SHORT,
	E_REG
}					t_flag;

typedef	struct		s_args
{
	uint8_t			mask;
	uint8_t			shift;
}					t_args;

typedef struct		s_champ
{
	const char		name[PROG_NAME_LENGTH + 1];
	int				id;
	size_t			size;
	uint8_t			bin[CHAMP_MAX_SIZE + 1];
	struct s_champ	*next;
}					t_champ;

typedef struct		s_opt
{
	uint8_t			v;
	int64_t			d;
	uint8_t			g : 1;
	uint16_t		ctmo;
}					t_opt;

typedef struct		s_proc
{
	int				id;
	uint8_t			flags;
	uint8_t			color;
	uint8_t			*pc;
	uint32_t		reg[REG_NUMBER + 1];
	size_t			lastlive;
	uint16_t		wait;
	uint8_t			crashed;
	struct s_proc	*next;
}					t_proc;

typedef struct		s_cw
{
	uint8_t			mem[MEM_SIZE];
	uint16_t		proc_count;
	t_proc			*prev;
	t_proc			*current;
	t_proc			*procs;
	int				cycle;
	int				cycle_to_die;
	t_opt			opt;
	uint8_t			n_champs;
	t_champ			*champs;
}					t_cw;

typedef int			(*t_instr)(t_proc *, uint8_t *);

extern t_cw			*g_cw;
extern t_op			g_op_tab[MAX_OP];

int					cw_live(t_proc *proc, uint8_t *op_code);
int					cw_ld(t_proc *proc, uint8_t *op_code);
int					cw_st(t_proc *proc, uint8_t *op_code);
int					cw_add(t_proc *proc, uint8_t *op_code);
int					cw_sub(t_proc *proc, uint8_t *op_code);
int					cw_and(t_proc *proc, uint8_t *op_code);
int					cw_or(t_proc *proc, uint8_t *op_code);
int					cw_xor(t_proc *proc, uint8_t *op_code);
int					cw_zjmp(t_proc *proc, uint8_t *op_code);
int					cw_ldi(t_proc *proc, uint8_t *op_code);
int					cw_sti(t_proc *proc, uint8_t *op_code);
int					cw_fork(t_proc *proc, uint8_t *op_code);
int					cw_lld(t_proc *proc, uint8_t *op_code);
int					cw_lldi(t_proc *proc, uint8_t *op_code);
int					cw_lfork(t_proc *proc, uint8_t *op_code);
int					cw_aff(t_proc *proc, uint8_t *op_code);

int					cw_nc_init(void);
int					cw_nc_update(void);
int					cw_nc_notify(uint16_t i, uint16_t c, uint8_t val);
int					cw_nc_exit(void);

void				cw_mem_dump(uint8_t *mem);
void				cw_mem_cpy(uint8_t *dst, uint8_t *src, size_t len,
						uint16_t p);
uint8_t				*cw_map_mem(uint8_t *mem, uint8_t *pc);
uint8_t				*cw_move_ptr(uint8_t const *pc, size_t len);
uint32_t			cw_mem_read(uint8_t **pc, uint8_t *ocp, size_t len,
						t_flag flags);
uint32_t			cw_read_arg(t_proc *proc, uint8_t **ptr, uint8_t n,
						uint8_t flags);
void				cw_update_carry(t_proc *proc, uint32_t value);

/*
** parse instruction arguments 
** return the pc offset or -1 in case of zboub (error)
*/
void				cw_vm_eval(t_proc *proc);

/*
** parse fichier cor 
*/
void				cw_vm_insert_sort(t_champ **head);
int					cw_vm_init(int ac, char **av, int r1);
int					cw_vm_run(void);
int					cw_exit(int ecode, char const *fmt, ...);

#endif
