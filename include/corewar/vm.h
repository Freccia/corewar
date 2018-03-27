/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar/vm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/26 17:15:36 by lfabbro          ###   ########.fr       */
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
	uint32_t	cycle;
	size_t		cycle_to_die;
	t_players	players;
	t_procs		procs;
}				t_vm;

extern t_vm		*g_vm;

int				vm_init(int ac, char **av, int r1);
int				vm_exit(int ecode, char const *fmt, ...);
int				vm_run(void);

#endif
