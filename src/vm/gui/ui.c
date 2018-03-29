/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/gui/ui.c                                        :+:      :+:    :+:   */
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
t_proc		*g_uiproc = NULL;
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
	[STATS_STEPI] = "Cycle by step    [up|down]: %d       ",
	[STATS_CYCLEL] = "Cycles/second limit [<|>]: %d       ",
	[STATS_CYCLE] = "Cycle : %d                           ",
	[STATS_PROCS] = "Processes : %d                       ",
	[STATS_CYCLE_TO_DIE] = "CYCLE_TO_DIE : %d             ",
	[STATS_CYCLE_DELTA] = "CYCLE_DELTA : %d               ",
	[STATS_NBR_LIVE] = "NBR_LIVE : %d                     ",
	[STATS_MAX_CHECKS] = "MAX_CHECKS : %d                 ",
};

static void	nc_pause(int *running)
{
	int ch;

	wattr_on(g_wstats, 0x200000, 0x0);
	wmove(g_wstats, g_stats[STATS_PAUSED][1], g_stats[STATS_PAUSED][0]);
	wprintw(g_wstats, *running ? "** PAUSED ** " : "** DEBUG **  ");
	wrefresh(g_wstats);
	*running = 0;
	while ((ch = getch()) != 32)
		if (ch == ERR)
			continue ;
		else if (ch == 27)
			vm_exit(EXIT_SUCCESS, "Good bye!\n");
		else if ((ch = cw_nc_onkey(ch)) < 0)
			vm_exit(EXIT_FAILURE, NULL);
		else if (ch == 1)
		{
			g_step = g_stepi - 1;
			break ;
		}
	wmove(g_wstats, g_stats[STATS_PAUSED][1], g_stats[STATS_PAUSED][0]);
	(*running = ch == 32) ? wprintw(g_wstats, "** RUNNING **") : 0;
	wrefresh(g_wstats);
	wattr_off(g_wstats, 0x200000, 0x0);
}

void		cw_nc_stats(uint8_t id, int value)
{
	int *pos;

	pos = g_stats[id];
	wmove(g_wstats, pos[1], pos[0]);
	wattr_on(g_wstats, 0x200000, 0x0);
	wprintw(g_wstats, g_statsstr[id], value);
	wattr_off(g_wstats, 0x200000, 0x0);
	wrefresh(g_wstats);
}

static char	*g_states[] = {
	[STATE_RUNNING] = "STATE_RUNNING",
	[STATE_WAITING] = "STATE_WAITING",
	[STATE_DIEING] = "STATE_DIEING",
	[STATE_PENDING] = "STATE_PENDING",
};

void		vm_guiproc(t_proc *proc)
{
	int y;
	int reg1;
	int reg2;

	g_uiproc = proc;
	y = 1;
	reg1 = 0;
	reg2 = 1;
	wattr_on(g_wprocs, 0x200000, 0x0);
	mvwprintw(g_wprocs, ++y, 4, "Processes: [o: reset | p: next]");
	mvwprintw(g_wprocs, y += 2, 4, "Process    (%s)% 10c", proc->owner->name, ' ');
	mvwprintw(g_wprocs, ++y, 4, "  PID      %-20d", proc->pid);
	mvwprintw(g_wprocs, ++y, 4, "  STATE:   %-20s", g_states[proc->state]);
	mvwprintw(g_wprocs, ++y, 4, "  PC:      %-20hhx", proc->pc);
	mvwprintw(g_wprocs, ++y, 4, "  CARRY:   %-20d", proc->carry);
	mvwprintw(g_wprocs, ++y, 4, "  LIVE:    %-20d", proc->lastlive);
	if (proc->state == STATE_WAITING)
		mvwprintw(g_wprocs, ++y, 4, "  WAIT:    %-20d", proc->wait);
	else
		++y;
	++y;
	mvwprintw(g_wprocs, ++y, 4, "  01 | %08x %08x | 02", proc->reg[reg1 += 2], proc->reg[reg2 += 2]);
	mvwprintw(g_wprocs, ++y, 4, "  03 | %08x %08x | 04", proc->reg[reg1 += 2], proc->reg[reg2 += 2]);
	mvwprintw(g_wprocs, ++y, 4, "  05 | %08x %08x | 06", proc->reg[reg1 += 2], proc->reg[reg2 += 2]);
	mvwprintw(g_wprocs, ++y, 4, "  07 | %08x %08x | 08", proc->reg[reg1 += 2], proc->reg[reg2 += 2]);
	mvwprintw(g_wprocs, ++y, 4, "  09 | %08x %08x | 0A", proc->reg[reg1 += 2], proc->reg[reg2 += 2]);
	mvwprintw(g_wprocs, ++y, 4, "  0B | %08x %08x | 0C", proc->reg[reg1 += 2], proc->reg[reg2 += 2]);
	mvwprintw(g_wprocs, ++y, 4, "  0D | %08x %08x | 0E", proc->reg[reg1 += 2], proc->reg[reg2 += 2]);
	mvwprintw(g_wprocs, ++y, 4, "  0F | %08x %08x | 0G", proc->reg[reg1], proc->reg[reg2]);
	wattr_off(g_wprocs, 0x200000, 0x0);
	wrefresh(g_wprocs);
}

int			vm_guiupdate(void)
{
	int ch;

	if (!g_vm->opt.g)
		return (YEP);
	if (g_step)
	{
		--g_step;
		return (YEP);
	}
	cw_nc_stats(STATS_CYCLE, (int)g_vm->cycle_total);
	cw_nc_stats(STATS_CYCLE_TO_DIE, (int)g_vm->cycle_to_die);
	cw_nc_stats(STATS_PROCS, (int)g_vm->procs.len);
	if (!g_running || (g_vm->opt.p && g_vm->opt.p == g_vm->cycle_total))
		nc_pause(&g_running);
	while ((ch = getch()) != ERR)
	{
		if (ch == 27)
			return (vm_exit(EXIT_SUCCESS, "Good bye!\n"));
		else if (ch == 32)
			nc_pause(&g_running);
		else if (cw_nc_onkey(ch))
			vm_exit(EXIT_FAILURE, NULL);
	}
	usleep((useconds_t)(1000000 / g_cyclel));
	return (YEP);
}

int			vm_guinotify(uint16_t i, uint16_t c, uint8_t val)
{
	int sq;
	int x;
	int y;

	if (!g_vm->opt.g)
		return (YEP);
	sq = getmaxy(g_wboard) - 2;
	x = 2 + ((i % sq) * 3);
	y = 1 + (i / sq);
	mvwaddch(g_wboard, y, x++, (chtype)DIGITS[(val / 16) % 16] | COLOR_PAIR(c));
	mvwaddch(g_wboard, y, x++, (chtype)DIGITS[val % 16] | COLOR_PAIR(c));
	mvwaddch(g_wboard, y, x++, ' ');
	wrefresh(g_wboard);
	return (YEP);
}
