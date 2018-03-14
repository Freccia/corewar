/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/14 13:46:32 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <libft.h>

# include "op.h"

// C'est degueulasse, mais c'est pour la norme...
# define SWAP_INT_C(a)	((unsigned int)(a & 0xff) >> 24)
# define SWAP_INT_B(a)	(((a) >> 8) & 0x0000ff00) | SWAP_INT_C(a) 
# define SWAP_INT_A(a)	(((a) << 8) & 0x00ff0000) | SWAP_INT_B(a) 
# define SWAP_INT(a)	(((a & 0xff) << 24) | SWAP_INT_A(a))

# define _CW_CARRY		(1 << 0)
# define _CW_PROCMAX	(101010)
# define _CW_MAGIC		SWAP_INT(COREWAR_EXEC_MAGIC)
# define _CW_HEAD_SZ	(16 + PROG_NAME_LENGTH + COMMENT_LENGTH)

typedef struct		s_opt
{
	uint8_t			v;
	int64_t			d;
	uint8_t			n : 1;
}					t_opt;

typedef struct		s_proc
{
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
	uint16_t		proc_idx;
	t_proc			*procs;
	size_t			cycle;
	uint16_t		cycle_to_die;
	t_opt			opt;
}					t_cw;

extern t_cw			*g_cw;

typedef int			(t_instr)(t_cw *cw, uint8_t a1, uint8_t a2, uint8_t a3);

int					cw_live(t_cw *cw, uint8_t a1, uint8_t a2, uint8_t a3);
int					cw_ld(t_cw *cw, uint8_t a1, uint8_t a2, uint8_t a3);
int					cw_st(t_cw *cw, uint8_t a1, uint8_t a2, uint8_t a3);
int					cw_add(t_cw *cw, uint8_t a1, uint8_t a2, uint8_t a3);
int					cw_sub(t_cw *cw, uint8_t a1, uint8_t a2, uint8_t a3);
int					cw_and(t_cw *cw, uint8_t a1, uint8_t a2, uint8_t a3);
int					cw_or(t_cw *cw, uint8_t a1, uint8_t a2, uint8_t a3);
int					cw_xor(t_cw *cw, uint8_t a1, uint8_t a2, uint8_t a3);
int					cw_zjmp(t_cw *cw, uint8_t a1, uint8_t a2, uint8_t a3);
int					cw_ldi(t_cw *cw, uint8_t a1, uint8_t a2, uint8_t a3);
int					cw_sti(t_cw *cw, uint8_t a1, uint8_t a2, uint8_t a3);
int					cw_fork(t_cw *cw, uint8_t a1, uint8_t a2, uint8_t a3);
int					cw_lld(t_cw *cw, uint8_t a1, uint8_t a2, uint8_t a3);
int					cw_lldi(t_cw *cw, uint8_t a1, uint8_t a2, uint8_t a3);
int					cw_lfork(t_cw *cw, uint8_t a1, uint8_t a2, uint8_t a3);
int					cw_aff(t_cw *cw, uint8_t a1, uint8_t a2, uint8_t a3);

int					cw_nc_init(void);
int					cw_nc_update(void);
int					cw_nc_notify(uint16_t i, uint16_t p, uint8_t val);
int					cw_nc_exit(void);

void				cw_mem_dump(uint8_t *mem);
int					cw_mem_write(t_cw *cw, uint8_t *pc, uint8_t value);

/*
** parse instruction arguments 
** return the pc offset or -1 in case of zboub (error)
*/
int					cw_vm_eval(t_cw *cw, uint8_t *pc);

/*
** parse fichier cor 
*/
t_proc				*cw_vm_parse(uint8_t *mem, const char *filename);
int					cw_vm_init(int ac, char **av);
int					cw_vm_run(void);
int					cw_exit(int ecode, char const *fmt, ...);

#endif
