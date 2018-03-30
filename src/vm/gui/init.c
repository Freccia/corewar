/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/gui/init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/12 18:15:53 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

WINDOW			*g_wboard = NULL;
WINDOW			*g_wstats = NULL;
WINDOW			*g_wprocs = NULL;

static float	ft_sqrt7(float x)
{
	unsigned int i;

	i = *(unsigned int*) &x;
	i += 127 << 23;
	i >>= 1;
	return (*(float*)&i);
}

static void		nc_colors(void)
{
	start_color();
	init_color(COLOR_WHITE, 0x12c, 0x12c, 0x12c);
	init_pair(0x2a, 0x8, COLOR_BLACK);
	init_pair(0, COLOR_BLACK, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(6, COLOR_WHITE, COLOR_GREEN);
	init_pair(7, COLOR_WHITE, COLOR_BLUE);
	init_pair(8, COLOR_WHITE, COLOR_RED);
	init_pair(9, COLOR_WHITE, COLOR_YELLOW);
	init_pair(10, COLOR_BLACK, COLOR_BLACK);
	init_pair(11, COLOR_BLACK, COLOR_GREEN);
	init_pair(12, COLOR_BLACK, COLOR_BLUE);
	init_pair(13, COLOR_BLACK, COLOR_RED);
	init_pair(14, COLOR_BLACK, COLOR_YELLOW);

}

static void		nc_draw_stats(void)
{
	gui_stats(STATS_STEPI, g_stepi);
	gui_stats(STATS_CYCLEL, g_cyclel);
	gui_stats(STATS_CYCLE, g_vm->cycle_total, g_vm->cycle_to_die - g_vm->cycle);
	gui_stats(STATS_PROCS, g_vm->procs.len);
	gui_stats(STATS_CYCLE_TO_DIE, g_vm->cycle_to_die);
	gui_stats(STATS_CYCLE_DELTA, CYCLE_DELTA);
	gui_stats(STATS_NBR_LIVE, g_vm->nbr_lives, NBR_LIVE);
	gui_stats(STATS_MAX_CHECKS, g_vm->max_checks, MAX_CHECKS);
}

void				gui_draw(void)
{
	int mx;
	int my;
	int x;
	int y;
	int a;

	mx = getmaxx(g_wboard);
	my = getmaxy(g_wboard);
	x = 2;
	y = 1;
	for (int i = 0; i < MEM_SIZE; ++i)
	{
		if (y + 1 >= my)
			break ;
		if (x + 4 > mx)
		{
			x = 2;
			++y;
		}
		if (g_map[i].print && !g_map[i].attrsl)
		{
			x += 3;
			continue ;
		}
		g_map[i].print = 1;
		if (g_map[i].attrs & GUI_BOLD)
			wattr_on(g_wboard, A_BOLD, NULL);
		if (g_map[i].attrs & GUI_NOCOLOR)
			a = COLOR_PAIR(0);
		else if (g_map[i].attrs & GUI_INV)
			a = COLOR_PAIR(g_map[i].color + VM_COLOR_INV);
		else if (g_map[i].attrs & GUI_HINT)
			a = COLOR_PAIR(g_map[i].color + VM_COLOR_HINT);
		else
			a = COLOR_PAIR(g_map[i].color);
		if (g_map[i].attrsl > 0)
		{
			if (!--g_map[i].attrsl)
			{
				g_map[i].attrs = 0;
				g_map[i].print = 0;
			}
		}
		mvwaddch(g_wboard, y, x++,
			(chtype)DIGITS[(g_vm->mem[i] / 16) % 16] | a);
		mvwaddch(g_wboard, y, x++,
			(chtype)DIGITS[g_vm->mem[i] % 16] | a);
		mvwaddch(g_wboard, y, x++, ' ');
		wattr_off(g_wboard, A_BOLD, NULL);
	}
	wrefresh(g_wboard);
}

static void		onresize(int sign)
{
	(void)sign;
	clear();
	wattr_on(g_wboard, 0x242a00, 0);
	box(g_wboard, 0x2a, 0x2a);
	wattr_off(g_wboard, 0x242a00, 0);
	wattr_on(g_wstats, 0x242a00, 0);
	box(g_wstats, 0x2a, 0x2a);
	wattr_off(g_wstats, 0x242a00, 0);
	wattr_on(g_wprocs, 0x242a00, 0);
	box(g_wprocs, 0x2a, 0x2a);
	wattr_off(g_wprocs, 0x242a00, 0);
	wrefresh(g_wstats);
	gui_draw();
	nc_draw_stats();
}

int				vm_guiinit(void)
{
	int sq;

	if (!g_vm->opt.g)
		return (YEP);
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(FALSE);
	nc_colors();
	sq = (int)ft_sqrt7(MEM_SIZE);
	if (!(g_wboard = subwin(stdscr, sq + 2, sq * 3 + 3, 0, 0)))
		return (WUT);
	if (!(g_wstats = subwin(stdscr, ((sq + 2) / 2) + 11, 50, 0, sq * 3 + 2)))
		return (WUT);
	if (!(g_wprocs = subwin(stdscr, ((sq + 2) / 2) - 10, 50, ((sq + 2) / 2) + 10, sq * 3 + 2)))
		return (WUT);
	ft_bzero(g_map, sizeof(g_map));
	onresize(0);
	signal(SIGWINCH, onresize);
	return (YEP);
}
