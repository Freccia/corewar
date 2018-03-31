/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/gui/init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/31 19:54:27 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"
#include <signal.h>

WINDOW		*g_wboard = NULL;
WINDOW		*g_wstats = NULL;
WINDOW		*g_wprocs = NULL;

static void	initcolors(void)
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

static void	redraw(void)
{
	int i;

	wattr_on(g_wboard, 0x242a00, 0);
	box(g_wboard, 0x2a, 0x2a);
	wattr_off(g_wboard, 0x242a00, 0);
	wattr_on(g_wstats, 0x242a00, 0);
	box(g_wstats, 0x2a, 0x2a);
	wattr_off(g_wstats, 0x242a00, 0);
	wattr_on(g_wprocs, 0x242a00, 0);
	box(g_wprocs, 0x2a, 0x2a);
	wattr_off(g_wprocs, 0x242a00, 0);
	wrefresh(g_wprocs);
	i = -1;
	while (++i < MEM_SIZE)
		g_map[i].print = 0;
	gui_drawboard();
	gui_drawstats();
}

static void	onresize(int sq)
{
	if (sq)
		usleep(600000);
	endwin();
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(FALSE);
	initcolors();
	clear();
	refresh();
	sq = (int)ft_sqrt(MEM_SIZE);
	g_wboard = subwin(stdscr, sq + 2, sq * 3 + 3, 0, 0);
	g_wstats = subwin(stdscr, ((sq + 2) / 2) + 11, 50, 0, sq * 3 + 2);
	g_wprocs = subwin(stdscr, ((sq + 2) / 2) - 10, 50,
		((sq + 2) / 2) + 10, sq * 3 + 2);
	redraw();
}

int			vm_guiinit(void)
{
	if (!g_vm->opt.g)
		return (YEP);
	ft_bzero(g_map, sizeof(g_map));
	onresize(0);
	signal(SIGWINCH, onresize);
	return (YEP);
}

int			vm_guiexit(void)
{
	if (!g_vm->opt.g)
		return (YEP);
	delwin(g_wboard);
	delwin(g_wstats);
	delwin(g_wprocs);
	endwin();
	return (YEP);
}
