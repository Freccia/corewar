/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/16 18:13:32 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <libft.h>

# include "cw_common.h"
# include "op.h"

# define _CW_CARRY		(1 << 0)
# define _CW_PROCMAX	(101010)
# define _CW_HEAD_SZ	(16 + PROG_NAME_LENGTH + COMMENT_LENGTH)

typedef int			(*t_instr)(uint8_t *);

typedef enum		e_range
{
	E_SHORT,
	E_LONG
}					t_range;

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
	uint8_t			reg[REG_NUMBER][REG_SIZE];
	size_t			lastlive;
	uint16_t		wait;
	struct s_proc	*next;
}					t_proc;

typedef struct		s_cw
{
	uint8_t			mem[MEM_SIZE];
	uint16_t		proc_count;
	t_proc			*prev;
	t_proc			*current;
	t_proc			*procs;
	size_t			cycle;
	int				cycle_to_die;
	t_opt			opt;
	uint8_t			n_champs;
	t_champ			*champs;
}					t_cw;

extern t_cw			*g_cw;
extern t_op			g_op_tab[MAX_OP];
extern t_instr		g_instr[MAX_OP];

int					cw_live(uint8_t *pc);
int					cw_ld(uint8_t *pc);
int					cw_st(uint8_t *pc);
int					cw_add(uint8_t *pc);
int					cw_sub(uint8_t *pc);
int					cw_and(uint8_t *pc);
int					cw_or(uint8_t *pc);
int					cw_xor(uint8_t *pc);
int					cw_zjmp(uint8_t *pc);
int					cw_ldi(uint8_t *pc);
int					cw_sti(uint8_t *pc);
int					cw_fork(uint8_t *pc);
int					cw_lld(uint8_t *pc);
int					cw_lldi(uint8_t *pc);
int					cw_lfork(uint8_t *pc);
int					cw_aff(uint8_t *pc);

int					cw_nc_init(void);
int					cw_nc_update(void);
int					cw_nc_notify(uint16_t i, uint16_t c, uint8_t val);
int					cw_nc_exit(void);

void				cw_mem_dump(uint8_t *mem);
int					cw_mem_write(t_cw *cw, uint8_t *pc, uint8_t value);
void				cw_mem_cpy(uint8_t *mem, uint8_t const *src, size_t len,
					uint16_t p);
uint8_t				*cw_map_mem(uint8_t *mem, uint8_t *pc);
uint8_t				*cw_move_pc(uint8_t *pc, size_t len);
int					cw_mem_read_dir(uint8_t **pc, size_t len, size_t move,
					t_range range);
int					cw_mem_read_ind(uint8_t **pc, size_t len, size_t move,
					t_range range);

/*
** parse instruction arguments 
** return the pc offset or -1 in case of zboub (error)
*/
int					cw_vm_eval(t_proc *proc);

/*
** takes instruction number, returns instruction cycles
*/
uint16_t			cw_instr_cycles(uint8_t instr);

/*
** parse fichier cor 
*/
uint16_t			cw_vm_parse(const char *filename, uint8_t *dest);
void				cw_vm_insert_sort(t_champ **head);
int					cw_vm_init(int ac, char **av, int r1);
int					cw_vm_run(void);
int					cw_exit(int ecode, char const *fmt, ...);

#endif
