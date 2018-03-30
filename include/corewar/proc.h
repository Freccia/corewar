/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar/proc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/30 17:54:42 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_PROC_H
# define COREWAR_PROC_H

# include <libft.h>

# include "player.h"

typedef enum		e_state
{
	STATE_RUNNING,
	STATE_PENDING,
	STATE_WAITING,
	STATE_DIEING
}					t_state;

typedef struct		s_proc
{
	struct s_proc	*next;
	t_player		*owner;
	pid_t			pid;
	uint8_t			carry;
	int32_t			reg[REG_NUMBER + 1];
	uint8_t			*pc;
	int32_t			lastlive;
	uint16_t		wait;
	t_state			state;
}					t_proc;

typedef struct		s_procs
{
	t_proc			*head;
	t_proc			*current;
	size_t			len;
	uint32_t		max_pid;
}					t_procs;

/*
** TODO: Doc
** @param proc
** @param owner
*/
void				vm_procinit(t_proc *proc, t_player *owner);

/*
** TODO: Doc
** @param dst
** @param src
** @param pc
*/
void				vm_procfork(t_proc *dst, t_proc *src, uint8_t *pc);

/*
** TODO: Doc
** @param procs
** @param proc
*/
void				vm_procspush(t_procs *procs, t_proc *proc);

/*
** TODO: Doc
** @param procs
** @param proc
*/
void				vm_procsrem(t_procs *procs, t_proc *proc);

/*
** TODO: Doc
** @param procs
*/
void				vm_procsclr(t_procs *procs);

#endif
