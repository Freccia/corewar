/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nc/update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/12 18:15:53 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

#define STATS_PAUSED 0
#define STATS_CYCLEL 1
#define STATS_CYCLE 2
#define STATS_PROCS 3
#define STATS_CYCLE_TO_DIE 4
#define STATS_CYCLE_DELTA 5
#define STATS_NBR_LIVE 6
#define STATS_MAX_CHECKS 7
#define STATS_PLAYERS 8

static int	g_cyclel = 50;
static int	g_stats[STATS_PLAYERS + MAX_PLAYERS][2] = {
	[STATS_PAUSED] = {4, 2},
	[STATS_CYCLEL] = {4, 4},
	[STATS_CYCLE] = {4, 6},
	[STATS_PROCS] = {4, 8},
	[STATS_CYCLE_TO_DIE] = {4, 10},
	[STATS_CYCLE_DELTA] = {4, 12},
	[STATS_NBR_LIVE] = {4, 14},
	[STATS_MAX_CHECKS] = {4, 16},
	[STATS_PLAYERS] = {4, 18},
};

static void	nc_stats_one(uint8_t id, const char *stats, ...)
{
	int		*pos;
	va_list	ap;

	pos = g_stats[id];
	wmove(g_wstats, pos[1], pos[0]);
	va_start(ap, stats);
	vwprintw(g_wstats, stats, ap);
	va_end(ap);
}

static void	nc_pause(int *running)
{
	int ch;

	*running = 0;
	nc_stats_one(STATS_PAUSED, "** PAUSED **");
	wrefresh(g_wstats);
	while ((ch = getch()) != 32)
	{
		if (ch == ERR)
			continue ;
		if (ch == 27)
			cw_exit(EXIT_SUCCESS, "Good bye!\n");
	}
	nc_stats_one(STATS_PAUSED, "** RUNNING **");
	wrefresh(g_wstats);
	*running = 1;
}

static void	nc_stats(void)
{
	nc_stats_one(STATS_CYCLEL, "Cycles/second limit : %d           ", g_cyclel);
	nc_stats_one(STATS_CYCLE, "Cycle : %d                       ", g_cw->cycle);
	nc_stats_one(STATS_PROCS, "Processes : %d              ", g_cw->proc_count);
	nc_stats_one(STATS_CYCLE_TO_DIE, "CYCLE_TO_DIE : %d  ", g_cw->cycle_to_die);
	nc_stats_one(STATS_CYCLE_DELTA, "CYCLE_DELTA : %d           ", CYCLE_DELTA);
	nc_stats_one(STATS_NBR_LIVE, "NBR_LIVE : %d                    ", NBR_LIVE);
	nc_stats_one(STATS_MAX_CHECKS, "MAX_CHECKS : %d              ", MAX_CHECKS);
	wrefresh(g_wstats);
}

static void	nc_cyclel(int ch)
{
	if (ch == KEY_RIGHT)
	{
		if (g_cyclel < 50)
			++g_cyclel;
		else if (g_cyclel >= 1000000 / 1.2)
			g_cyclel = 1000000;
		else if (g_cyclel < 1000000 / 1.2)
			g_cyclel *= 1.2;
	}
	else if (ch == KEY_LEFT)
	{
		if (g_cyclel > 1)
		{
			if (g_cyclel < 50)
				--g_cyclel;
			else
				g_cyclel /= 1.2;
		}
	}
}

int			cw_nc_update(void)
{
	int ch;
	static int running = 0;

	if (!g_cw->opt.g)
		return (YEP);
	wattr_on(g_wstats, 0x200000, 0x0);
	nc_stats();
	if (!running)
		nc_pause(&running);
	while ((ch = getch()) != ERR)
	{
		if (ch == 27)
			return (cw_exit(EXIT_SUCCESS, "Good bye!\n"));
		else if (ch == 32)
			nc_pause(&running);
		else if (ch == KEY_RIGHT || ch == KEY_LEFT)
			nc_cyclel(ch);
	}
	wattr_off(g_wstats, 0x200000, 0x0);
	usleep((useconds_t)(1000000 / g_cyclel));
	return (YEP);
}
