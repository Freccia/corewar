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
t_cell		g_map[MEM_SIZE];
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
		else if ((ch = gui_onkey(ch)) < 0)
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

void		gui_stats(uint8_t id, int value)
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

static void	printreg(t_proc *proc, int32_t reg)
{
	if (reg)
		wattr_on(g_wprocs, (attr_t)COLOR_PAIR(proc->owner->idx + 1), 0x0);
	wprintw(g_wprocs, "0x%08x ", reg);
	if (reg)
		wattr_off(g_wprocs, (attr_t)COLOR_PAIR(proc->owner->idx + 1), 0x0);
}

void		vm_guiplayer(t_player *player)
{
	int y;
	int x;

	wattr_on(g_wstats, 0x200000, 0x0);
	y = g_stats[STATS_PLAYERS][1] + (player->idx * 4);
	x = g_stats[STATS_PLAYERS][0];
	mvwprintw(g_wstats, y, x, "Player %d: ", player->id);

	wattr_on(g_wstats, (attr_t)COLOR_PAIR(player->idx + 1), 0x0);
	wprintw(g_wstats, "%s", player->name);
	wattr_off(g_wstats, (attr_t)COLOR_PAIR(player->idx + 1), 0x0);
	mvwprintw(g_wstats, ++y, x, "  Last live : %-20d       ", player->lastlive);
	wrefresh(g_wstats);
}

void		vm_guiproc(t_proc *proc)
{
	int y;
	int reg;

	if (!g_vm->opt.g)
		return ;
	g_uiproc = proc;
	y = 1;
	reg = 0;
	wattr_on(g_wprocs, 0x200000, 0x0);
	mvwprintw(g_wprocs, ++y, 4, "Processes: [o: reset | p: next]");
	mvwprintw(g_wprocs, y += 2, 4, "Process    %d ", proc->pid);
	wattr_on(g_wprocs, (attr_t)COLOR_PAIR(proc->owner->idx + 1), 0x0);
	wprintw(g_wprocs, "(%s)% 10c", proc->owner->name, ' ');
	wattr_off(g_wprocs, (attr_t)COLOR_PAIR(proc->owner->idx + 1), 0x0);
	mvwprintw(g_wprocs, ++y, 4, "  STATE:   %-20s", g_states[proc->state]);
	mvwprintw(g_wprocs, ++y, 4, "  PC:      %02hhx (%d)% 16c", *proc->pc, proc->pc - g_vm->mem, ' ');
	mvwprintw(g_wprocs, ++y, 4, "  CARRY:   %-20d", proc->carry);
	mvwprintw(g_wprocs, ++y, 4, "  LIVE:    %-20d", proc->lastlive);
	if (proc->state == STATE_WAITING)
		mvwprintw(g_wprocs, ++y, 4, "  WAIT:    %-20d", proc->wait);
	else
		++y;
	++y;
	wattr_off(g_wprocs, 0x200000, 0x0);
	while (++reg <= REG_NUMBER)
	{
		mvwprintw(g_wprocs, ++y, 4, "  %02x | ", reg);
		printreg(proc, proc->reg[reg]);
		printreg(proc, proc->reg[++reg]);
	}
	wrefresh(g_wprocs);
}

int			vm_guiupdate(void)
{
	int			ch;
	t_player	*player;

	if (!g_vm->opt.g)
		return (YEP);
	gui_draw();
	if (g_step)
	{
		--g_step;
		return (YEP);
	}
	gui_stats(STATS_CYCLE, (int)g_vm->cycle_total);
	gui_stats(STATS_CYCLE_TO_DIE, (int)g_vm->cycle_to_die);
	gui_stats(STATS_PROCS, (int)g_vm->procs.len);
	player = g_vm->players.head;
	while (player)
	{
		vm_guiplayer(player);
		player = player->next;
	}
	if (!g_running || (g_vm->opt.p && g_vm->opt.p == g_vm->cycle_total))
		nc_pause(&g_running);
	while ((ch = getch()) != ERR)
	{
		if (ch == 27)
			return (vm_exit(EXIT_SUCCESS, "Good bye!\n"));
		else if (ch == 32)
			nc_pause(&g_running);
		else if (gui_onkey(ch))
			vm_exit(EXIT_FAILURE, NULL);
	}
	usleep((useconds_t)(1000000 / g_cyclel));
	return (YEP);
}

int			vm_guinotify(uint16_t i, int color, int attrs, uint8_t lt)
{
	if (!g_vm->opt.g)
		return (YEP);
	if (color >= 0)
		g_map[i].color = (uint8_t)color;
	g_map[i].attrs = (uint16_t)attrs;
	g_map[i].attrsl = lt;
	return (YEP);
}
