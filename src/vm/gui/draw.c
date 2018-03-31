/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/gui/draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/30 22:24:27 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static char	*g_states[] = {
	[STATE_RUNNING] = "Running",
	[STATE_WAITING] = "Waiting",
	[STATE_DIEING] = "Dieing",
	[STATE_PENDING] = "Pending",
};

void		gui_drawboard(void)
{
	int x;
	int y;
	int a;
	int i;

	x = 2;
	y = 1;
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (y + 1 >= getmaxy(g_wboard))
			break ;
		if (x + 4 > getmaxx(g_wboard) && (x = 2))
			++y;
		if (g_map[i].print && !g_map[i].lifetime && (x += 3))
			continue ;
		g_map[i].print = 1;
		a = gui_cellattrs(g_map + i);
		mvwaddch(g_wboard, y, x++, (chtype)DGTS[(g_vm->mem[i] / 16) % 16] | a);
		mvwaddch(g_wboard, y, x++, (chtype)DGTS[g_vm->mem[i] % 16] | a);
		mvwaddch(g_wboard, y, x++, ' ');
		wattr_off(g_wboard, A_BOLD, NULL);
	}
	wrefresh(g_wboard);
}

void		gui_drawstats(void)
{
	gui_stats(STATS_PAUSED, g_running ? "** RUNNING **" : "** PAUSED **");
	gui_stats(STATS_STEPI, g_stepi);
	gui_stats(STATS_CYCLEL, g_cyclel);
	gui_stats(STATS_CYCLE, g_vm->cycle_total, g_vm->cycle_to_die - g_vm->cycle);
	gui_stats(STATS_PROCS, g_vm->procs.len);
	gui_stats(STATS_CYCLE_TO_DIE, g_vm->cycle_to_die);
	gui_stats(STATS_CYCLE_DELTA, CYCLE_DELTA);
	gui_stats(STATS_NBR_LIVE, g_vm->nbr_lives, NBR_LIVE);
	gui_stats(STATS_MAX_CHECKS, g_vm->max_checks, MAX_CHECKS);
}

static void	print2reg(t_proc *proc, int32_t *reg, int *y)
{
	mvwprintw(g_wprocs, ++*y, 4, "  %02x |  ", *reg);
	if (proc->reg[*reg])
		wattr_on(g_wprocs, (attr_t)COLOR_PAIR(proc->owner->idx + 1), 0x0);
	wprintw(g_wprocs, "0x%08x ", proc->reg[*reg]);
	if (proc->reg[*reg])
		wattr_off(g_wprocs, (attr_t)COLOR_PAIR(proc->owner->idx + 1), 0x0);
	if (proc->reg[++*reg])
		wattr_on(g_wprocs, (attr_t)COLOR_PAIR(proc->owner->idx + 1), 0x0);
	wprintw(g_wprocs, "0x%08x ", proc->reg[*reg]);
	if (proc->reg[*reg])
		wattr_off(g_wprocs, (attr_t)COLOR_PAIR(proc->owner->idx + 1), 0x0);
	mvwprintw(g_wprocs, *y, 33, "  | %02x", *reg);
}

void		vm_guiwinner(t_player *player)
{
	if (!g_vm->opt.g)
		return ;
	wattr_on(g_wstats, 0x200000, 0x0);
	mvwprintw(g_wstats, 38, 4, "The winner is: ");
	wattr_on(g_wstats, (attr_t)COLOR_PAIR(player->idx + 1), 0x0);
	wprintw(g_wstats, "%.20s", player->name);
	wattr_off(g_wstats, (attr_t)COLOR_PAIR(player->idx + 1), 0x0);
	mvwprintw(g_wstats, 40, 4, "Press any key to exit... ");
	wattr_off(g_wstats, 0x200000, 0x0);
	wrefresh(g_wstats);
	while (getch() == ERR)
		;
}

void		vm_guiproc(t_proc *proc)
{
	int y;
	int reg;

	if (!g_vm->opt.g || !proc)
		return ;
	g_uiproc = proc;
	y = 1;
	reg = 0;
	wattr_on(g_wprocs, 0x200000, 0x0);
	mvwprintw(g_wprocs, ++y, 4, "Processes: [o: reset | p: next]");
	mvwprintw(g_wprocs, y += 2, 4, "Process    %d ", proc->pid);
	wattr_on(g_wprocs, (attr_t)COLOR_PAIR(proc->owner->idx + 1), 0x0);
	wprintw(g_wprocs, "(%.20s) %10c", proc->owner->name, ' ');
	wattr_off(g_wprocs, (attr_t)COLOR_PAIR(proc->owner->idx + 1), 0x0);
	mvwprintw(g_wprocs, ++y, 4, "  STATE:   %-20s", g_states[proc->state]);
	mvwprintw(g_wprocs, ++y, 4, "  PC:      %02hhx (%d)% 16c",
		*proc->pc, proc->pc - g_vm->mem, ' ');
	mvwprintw(g_wprocs, ++y, 4, "  CARRY:   %-20d", proc->carry);
	mvwprintw(g_wprocs, ++y, 4, "  LIVE:    %-20d", proc->last_live);
	mvwprintw(g_wprocs, ++y, 4, "  WAIT:    %-20d", proc->wait);
	wattr_off(g_wprocs, 0x200000, 0x0);
	++y;
	while (++reg <= REG_NUMBER)
		print2reg(proc, &reg, &y);
	wrefresh(g_wprocs);
}
