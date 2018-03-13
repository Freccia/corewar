/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/13 18:06:45 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "./op.h"

# define _CW_CARRY (1 << 0)
# define _CW_PROCMAX (101010)

typedef struct		s_proc
{
	uint8_t			flags;
	uint8_t			color;
	uint8_t			*pc;
	uint8_t			reg[REG_NUMBER][REG_SIZE];
	size_t			lastlive;
	uint16_t		wait;
}					t_proc;

typedef struct		s_cw
{
	uint8_t			mem[MEM_SIZE];
	uint16_t		proc_count;
	uint16_t		proc_idx;
	t_proc			procs[_CW_PROCMAX];
	size_t			cycle;
	uint16_t		cycle_to_die;
}					t_cw;

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

int					cw_ncinit(t_cw *cw);
int					cw_ncupdate(t_cw *cw);
int					cw_ncnotify(t_cw *cw, uint16_t i, uint16_t p, uint8_t val);
int					cw_ncexit(t_cw *cw);

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
int					cw_vm_parse(uint8_t *mem, const char *filename);
int					cw_vm_run(t_cw *cw);

#endif
