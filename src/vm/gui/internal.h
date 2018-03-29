/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/gui/internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/13 18:06:45 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NC_INTERNAL_H
# define NC_INTERNAL_H

# include <ncurses.h>

# include "corewar.h"

# define DIGITS "0123456789abcdefg"

# define STATS_PAUSED 0
# define STATS_CYCLEL 1
# define STATS_CYCLE 2
# define STATS_PROCS 3
# define STATS_CYCLE_TO_DIE 4
# define STATS_CYCLE_DELTA 5
# define STATS_NBR_LIVE 6
# define STATS_MAX_CHECKS 7
# define STATS_PLAYERS 8
# define STATS_STEPI 9

typedef int		(t_keyh)(int ch);

extern WINDOW	*g_wboard;
extern WINDOW	*g_wstats;
extern WINDOW	*g_wprocs;
extern int		g_cyclel;
extern int		g_running;
extern int		g_stepi;
extern t_proc	*g_uiproc;

int				cw_nc_onkey(int ch);
void			cw_nc_stats(uint8_t id, int value);

#endif
