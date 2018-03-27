/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar/proc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/26 17:15:36 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_PROC_H
# define COREWAR_PROC_H

# include <libft.h>

# include "player.h"

typedef struct		s_proc
{
	struct s_proc	*next;
	t_player		*owner;
	pid_t			pid;
	uint8_t			flags;
	int32_t			reg[REG_NUMBER + 1];
	uint8_t			*pc;
	size_t			lastlive;
	uint16_t		wait;
	uint8_t			crashed;
}					t_proc;

#endif
