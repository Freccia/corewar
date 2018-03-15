/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/15 18:11:13 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <libft.h>

# include "op.h"

// C'est degueulasse, mais c'est pour la norme...
# define SWAP_INT_C(a)	((unsigned int)((a) & 0xff) >> 24)
# define SWAP_INT_B(a)	((((a) >> 8) & 0x0000ff00) | SWAP_INT_C(a))
# define SWAP_INT_A(a)	((((a) << 8) & 0x00ff0000) | SWAP_INT_B(a))
# define SWAP_INT(a)	((((a) & 0xff) << 24) | SWAP_INT_A(a))

# define _CW_CARRY		(1 << 0)
# define _CW_PROCMAX	(101010)
# define _CW_MAGIC		SWAP_INT(COREWAR_EXEC_MAGIC)
# define _CW_HEAD_SZ	(16 + PROG_NAME_LENGTH + COMMENT_LENGTH)
# define _CW_N_OP		16

typedef enum		e_range
{
	E_SHORT,
	E_LONG
}					t_range;

typedef struct		s_champs
{
	char			file_name[PROG_NAME_LENGTH];
	const char		name[PROG_NAME_LENGTH];
	int				id;
}					t_champs;

typedef struct		s_opt
{
	uint8_t			v;
	int64_t			d;
	uint8_t			g : 1;
}					t_opt;

typedef struct		s_proc
{
	char			name[128];
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
	t_champs		champs[MAX_PLAYERS];
}					t_cw;

extern t_cw			*g_cw;
extern t_op			g_op_tab[_CW_N_OP];

typedef int			(*t_instr)(uint8_t *);

int					cw_live(uint8_t *mem);
int					cw_ld(uint8_t *mem);
int					cw_st(uint8_t *mem);
int					cw_add(uint8_t *mem);
int					cw_sub(uint8_t *mem);
int					cw_and(uint8_t *mem);
int					cw_or(uint8_t *mem);
int					cw_xor(uint8_t *mem);
int					cw_zjmp(uint8_t *mem);
int					cw_ldi(uint8_t *mem);
int					cw_sti(uint8_t *mem);
int					cw_fork(uint8_t *mem);
int					cw_lld(uint8_t *mem);
int					cw_lldi(uint8_t *mem);
int					cw_lfork(uint8_t *mem);
int					cw_aff(uint8_t *mem);

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
int					cw_mem_read(uint8_t *pc, size_t len, size_t move,
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
int					cw_vm_init(int ac, char **av, int r1);
int					cw_vm_run(void);
int					cw_exit(int ecode, char const *fmt, ...);

#endif
