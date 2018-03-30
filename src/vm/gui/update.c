/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/gui/update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/12 18:15:53 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

int			g_cyclel = 50;
int			g_running = 0;
int			g_stepi = 5;
int			g_dinstr = 0;
t_proc		*g_uiproc = NULL;
t_cell		g_map[MEM_SIZE];
static int	g_step = 0;
static int	g_stats[STATS_PLAYERS + MAX_PLAYERS][2] = {
	[STATS_PAUSED] = {4, 2},
	[STATS_STEPI] = {4, 4},
	[STATS_CYCLEL] = {4, 6},
	[STATS_CYCLE] = {4, 8},
	[STATS_PROCS] = {4, 10},
	[STATS_CYCLE_TO_DIE] = {4, 12},
	[STATS_CYCLE_DELTA] = {4, 14},
	[STATS_NBR_LIVE] = {4, 16},
	[STATS_MAX_CHECKS] = {4, 18},
	[STATS_PLAYERS] = {4, 20},
};
static char	*g_statsstr[STATS_PLAYERS + MAX_PLAYERS] = {
	[STATS_PAUSED] = "%s      ",
	[STATS_STEPI] = "Cycle by step    [up|down]: %d       ",
	[STATS_CYCLEL] = "Cycles/second limit [<|>]: %d       ",
	[STATS_CYCLE] = "Cycle : %-8d (%d)                    ",
	[STATS_PROCS] = "Processes : %d                       ",
	[STATS_CYCLE_TO_DIE] = "CYCLE_TO_DIE : %d             ",
	[STATS_CYCLE_DELTA] = "CYCLE_DELTA : %d               ",
	[STATS_NBR_LIVE] = "NBR_LIVE : %d/%d                  ",
	[STATS_MAX_CHECKS] = "MAX_CHECKS : %d/%d              ",
};

void		gui_stats(int id, ...)
{
	int		*pos;
	va_list	ap;

	pos = g_stats[id];
	wmove(g_wstats, pos[1], pos[0]);
	wattr_on(g_wstats, 0x200000, 0x0);
	va_start(ap, id);
	vwprintw(g_wstats, g_statsstr[id], ap);
	va_end(ap);
	wattr_off(g_wstats, 0x200000, 0x0);
	wrefresh(g_wstats);
}

static void	drawplayer(t_player *player)
{
	int y;
	int x;

	wattr_on(g_wstats, 0x200000, 0x0);
	y = g_stats[STATS_PLAYERS][1] + (player->idx * 4);
	x = g_stats[STATS_PLAYERS][0];
	mvwprintw(g_wstats, y, x, "Player %d: ", player->id);
	wattr_on(g_wstats, (attr_t)COLOR_PAIR(player->idx + 1), 0x0);
	wprintw(g_wstats, "%.20s", player->name);
	wattr_off(g_wstats, (attr_t)COLOR_PAIR(player->idx + 1), 0x0);
	mvwprintw(g_wstats, ++y, x, "  Last live : %-20d       ", player->lastlive);
	mvwprintw(g_wstats, ++y, x, "  Lives in current period : %-6d       ",
		player->lives_in_periode);
	wattr_off(g_wprocs, 0x200000, 0x0);
	wrefresh(g_wstats);
}

static void	dopause(void)
{
	int ch;

	gui_stats(STATS_PAUSED, g_running ? "** PAUSED ** " : "** DEBUG **  ");
	g_running = 0;
	while ((ch = getch()) != 32)
		if (ch == ERR)
			continue ;
		else if (ch == 27)
			vm_exit(EXIT_SUCCESS, NULL);
		else if ((ch = gui_onkey(ch)) < 0)
			vm_exit(EXIT_FAILURE, NULL);
		else if (ch == 1)
		{
			g_step = g_stepi - 1;
			break ;
		}
	if ((g_running = ch == 32))
		gui_stats(STATS_PAUSED, "** RUNNING **");
}

static int	keymap(void)
{
	int ch;

	while ((ch = getch()) != ERR)
	{
		if (ch == 27)
			return (vm_exit(EXIT_SUCCESS, NULL));
		else if (ch == 32)
			dopause();
		else if (gui_onkey(ch) < 0)
			vm_exit(EXIT_FAILURE, NULL);
	}
	return (YEP);
}

int			vm_guiupdate(void)
{
	t_player	*player;

	if (!g_vm->opt.g)
		return (YEP);
	gui_drawboard();
	if (g_step)
	{
		--g_step;
		return (YEP);
	}
	gui_drawstats();
	player = g_vm->players.head;
	while (player)
	{
		drawplayer(player);
		player = player->next;
	}
	if (!g_running || (g_vm->opt.p && g_vm->opt.p == g_vm->cycle_total))
		dopause();
	usleep((useconds_t)(1000000 / g_cyclel));
	return (keymap());
}
