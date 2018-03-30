/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/30 10:49:49 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VM_H
# define COREWAR_VM_H

# include "player.h"
# include "proc.h"
# include "opt.h"

typedef struct	s_vm
{
	uint8_t		mem[MEM_SIZE];
	t_opt		opt;
	int32_t		cycle;
	int32_t		cycle_to_die;
	int32_t		cycle_total;
	t_players	players;
	t_procs		procs;
}				t_vm;

extern t_vm		*g_vm;

/*
** TODO: Doc
** @param ac 
** @param av 
** @param r1 
** @return 
*/
int				vm_init(int ac, char **av);

/*
** TODO: Doc
** @param ecode 
** @param fmt 
** @param ... 
** @return 
*/
int				vm_exit(int ecode, char const *fmt, ...);

/*
** TODO: Doc
** @param mem
*/
void			vm_dump(uint8_t *mem);

/*
** TODO: Doc
** @return 
*/
void			vm_run(void);

#endif
