
int _draw_live_breakdown(int arg0) {
	rcx = *_stdscr;
	var_8 = **___stack_chk_guard;
	var_28 = arg0;
	var_2C = *(int32_t *)(var_28 + 0x10) + *(int32_t *)(var_28 + 0xc) + *(int32_t *)(var_28 + 0x4) + *(int32_t *)(var_28 + 0x8);
	var_38 = 0x0;
	wattr_on(*rcx, 0x202a00, 0x0);
	printw("[");
	wattr_off(**_stdscr, 0x202a00, 0x0);
	if (var_2C > 0x0) {
		for (var_30 = 0x1; var_30 < 0x5; var_30 = var_30 + 0x1) {
			rcx = *_stdscr;
			xmm0 = intrinsic_movsd(xmm0, *qword);
			xmm1 = intrinsic_cvtsi2sd(xmm1, *(int32_t *)(var_28 + sign_extend_64(var_30) * 0x4));
			xmm1 = intrinsic_mulsd(xmm1, xmm0);
			xmm0 = intrinsic_cvtsi2sd(xmm0, var_2C);
			xmm1 = intrinsic_divsd(xmm1, xmm0);
			xmm0 = intrinsic_movaps(xmm0, xmm1);
			*(int32_t *)(rbp + (sign_extend_64(var_30) * 0x4 - 0x20)) = intrinsic_cvttsd2si(round(xmm0), xmm0);
			wattr_on(*rcx, var_30 << 0x8 | 0x200000, 0x0);
			var_34 = 0x0;
			do {
				var_5D = 0x0;
				if (var_34 < *(int32_t *)(rbp + (sign_extend_64(var_30) * 0x4 - 0x20))) {
					var_5D = var_38 < 0x32 ? 0x1 : 0x0;
				}
				if ((var_5D & 0x1) == 0x0) {
					break;
				}
				waddch(**_stdscr, 0x2d);
				var_34 = var_34 + 0x1;
				var_38 = var_38 + 0x1;
			} while (true);
			wattr_off(**_stdscr, var_30 << 0x8 | 0x200000, 0x0);
		}
	}
	while (var_38 < 0x32) {
		waddch(**_stdscr, 0x2d);
		var_38 = var_38 + 0x1;
	}
	wattr_on(**_stdscr, 0x202a00, 0x0);
	printw("]");
	rax = wattr_off(**_stdscr, 0x202a00, 0x0);
	if (**___stack_chk_guard != var_8) {
		rax = __stack_chk_fail();
	}
	return rax;
}


int _redraw(int arg0) {
	rax = _options;
	var_8 = arg0;
	if (*(int32_t *)(rax + 0x4) != 0x0) {
		gettimeofday(&var_18, 0x0);
		var_28 = (sign_extend_64(0x3e8 / *(int32_t *)(var_8 + 0x15064)) - (sign_extend_64(var_10) - *_redraw.last_usec) + (var_18 - *_redraw.last_sec) * 0x3e8) % sign_extend_64(0x3e8 / *(int32_t *)(var_8 + 0x15064));
		if (var_28 > 0x0) {
			usleep(var_28 * 0x3e8);
		}
		_draw_stats(var_8);
		_draw_memory(var_8);
		_draw_sep(0x0);
		_draw_sep(0xc4);
		_draw_sep(0xfd);
		_draw_line(0x0);
		_draw_line(0x43);
		wrefresh(**_stdscr);
		rax = gettimeofday(&var_18, 0x0);
		*_redraw.last_sec = var_18;
		*_redraw.last_usec = sign_extend_64(var_10);
	}
	return rax;
}

int _draw_stats(int arg0) {
	var_8 = arg0;
	wattr_on(**_stdscr, 0x200000, 0x0);
	wmove(**_stdscr, 0x2, 0xc7);
	rax = wclrtoeol(**_stdscr);
	rcx = "** PAUSED **";
	var_C = 0x1;
	rdx = 0x2;
	if (*(int32_t *)(var_8 + 0x15060) != 0x0) {
		rcx = "** RUNNING **";
	}
	mvprintw(rdx, 0xc7, rcx);
	wmove(**_stdscr, var_C + 0x3, 0xc7);
	wclrtoeol(**_stdscr);
	mvprintw(var_C + 0x3, 0xc7, "Cycles/second limit : %u");
	wmove(**_stdscr, var_C + 0x6, 0xc7);
	wclrtoeol(**_stdscr);
	mvprintw(var_C + 0x6, 0xc7, "Cycle : %u");
	wmove(**_stdscr, var_C + 0x8, 0xc7);
	wclrtoeol(**_stdscr);
	mvprintw(var_C + 0x8, 0xc7, "Processes : %u");
	var_C = var_C + 0x8;
	wattr_off(**_stdscr, 0x200000, 0x0);
	for (var_18 = *(var_8 + 0x15018); var_18 != 0x0; var_18 = *(var_18 + 0x20)) {
		rcx = *_stdscr;
		var_20 = *(var_18 + 0x8);
		wattr_on(*rcx, 0x200000, 0x0);
		wmove(**_stdscr, var_C + 0x2, 0xc7);
		printw("Player %d : ");
		wattr_off(**_stdscr, 0x200000, 0x0);
		wattr_on(**_stdscr, *(int32_t *)var_20 << 0x8 | 0x200000, 0x0);
		printw("%.41s");
		wattr_off(**_stdscr, *(int32_t *)var_20 << 0x8 | 0x200000, 0x0);
		wattr_on(**_stdscr, 0x200000, 0x0);
		wmove(**_stdscr, var_C + 0x3, 0xc7);
		printw("  Last live :               % 7d");
		wmove(**_stdscr, var_C + 0x4, 0xc7);
		printw("  Lives in current period : % 7d");
		wattr_off(**_stdscr, 0x200000, 0x0);
		var_C = var_C + 0x4;
	}
	wmove(**_stdscr, var_C + 0x2, 0xc7);
	wattr_on(**_stdscr, 0x200000, 0x0);
	printw("Live breakdown for current period :");
	wattr_off(**_stdscr, 0x200000, 0x0);
	wmove(**_stdscr, var_C + 0x3, 0xc7);
	wclrtoeol(**_stdscr);
	_draw_live_breakdown(var_8 + 0x15038);
	rax = var_C + 0x3;
	var_C = rax + 0x1;
	wmove(**_stdscr, rax + 0x2, 0xc7);
	wattr_on(**_stdscr, 0x200000, 0x0);
	printw("Live breakdown for last period :");
	wattr_off(**_stdscr, 0x200000, 0x0);
	wmove(**_stdscr, var_C + 0x2, 0xc7);
	wclrtoeol(**_stdscr);
	_draw_live_breakdown(var_8 + 0x1504c);
	wattr_on(**_stdscr, 0x200000, 0x0);
	wmove(**_stdscr, var_C + 0x4, 0xc7);
	wclrtoeol(**_stdscr);
	mvprintw(var_C + 0x4, 0xc7, "CYCLE_TO_DIE : %u");
	wmove(**_stdscr, var_C + 0x6, 0xc7);
	wclrtoeol(**_stdscr);
	mvprintw(var_C + 0x6, 0xc7, "CYCLE_DELTA : %u");
	wmove(**_stdscr, var_C + 0x8, 0xc7);
	wclrtoeol(**_stdscr);
	mvprintw(var_C + 0x8, 0xc7, "NBR_LIVE : %u");
	wmove(**_stdscr, var_C + 0xa, 0xc7);
	wclrtoeol(**_stdscr);
	mvprintw(var_C + 0xa, 0xc7, "MAX_CHECKS : %u");
	var_C = var_C + 0xa;
	wattr_off(**_stdscr, 0x200000, 0x0);
	rax = _game_ended(var_8);
	if (rax != 0x0) {
		var_28 = _get_winner(var_8);
		wmove(**_stdscr, var_C + 0x2, 0xc7);
		wattr_on(**_stdscr, 0x200000, 0x0);
		printw("The winner is : ");
		wattr_on(**_stdscr, *(int32_t *)var_28 << 0x8, 0x0);
		printw("%.60s");
		wattr_off(**_stdscr, *(int32_t *)var_28 << 0x8, 0x0);
		wattr_off(**_stdscr, 0x200000, 0x0);
		wmove(**_stdscr, var_C + 0x4, 0xc7);
		wattr_on(**_stdscr, 0x200000, 0x0);
		printw("Press any key to finish");
		rax = wattr_off(**_stdscr, 0x200000, 0x0);
	}
	return rax;
}

void _draw_memory(int arg0) {
	var_8 = arg0;
	for (var_C = 0x0; var_C < 0x40; var_C = var_C + 0x1) {
		for (var_10 = 0x0; var_10 < 0x40; var_10 = var_10 + 0x1) {
			var_30 = ((var_C << 0x6) + var_10) * 0x14 + var_8 + 0x1000;
			if (*(int32_t *)(var_30 + 0x4) != 0x0) {
				var_34 = *(int32_t *)(var_30 + 0x4);
			}
			else {
				var_34 = 0x2a;
			}
			var_14 = var_34;
			var_18 = (*(int32_t *)var_30 > 0x0 ? 0x1 : 0x0) & 0x1 & 0xff;
			var_1C = (*(int32_t *)(var_30 + 0x8) > 0x0 ? 0x1 : 0x0) & 0x1 & 0xff;
			if ((*(int32_t *)(var_8 + 0x15060) != 0x0) && (var_1C != 0x0)) {
				rcx = *(int32_t *)(var_30 + 0x8);
				*(int32_t *)(var_30 + 0x8) = rcx + 0x1;
				if (rcx == 0x32) {
					*(int32_t *)(var_30 + 0x8) = 0x0;
				}
			}
			if (*(int32_t *)(var_30 + 0x10) > 0x0) {
				var_38 = *(int32_t *)(var_30 + 0xc);
			}
			else {
				var_38 = 0x0;
			}
			var_20 = var_38;
			if ((*(int32_t *)(var_8 + 0x15060) != 0x0) && (var_20 != 0x0)) {
				rcx = *(int32_t *)(var_30 + 0x10);
				*(int32_t *)(var_30 + 0x10) = rcx + 0x1;
				if (rcx == 0x32) {
					*(int32_t *)(var_30 + 0x10) = 0x0;
				}
			}
			if (var_20 != 0x0) {
				var_24 = (var_20 | 0x10) << 0x8 | 0x200000;
			}
			else {
				var_24 = var_14 << 0x8;
				if (var_18 != 0x0) {
					var_24 = var_24 | 0x40000;
				}
				if ((var_1C | ((*(int32_t *)(var_30 + 0x4) != 0x0 ? 0x1 : 0x0) ^ 0xff) & 0x1 & 0xff) != 0x0) {
					var_24 = var_24 | 0x200000;
				}
			}
			wattr_on(**_stdscr, var_24, 0x0);
			var_40 = var_10 * 0x3 + 0x3;
			var_44 = var_C + 0x2;
			if (*(int32_t *)0x1000095e0 != 0x0) {
				var_48 = 0xff;
			}
			else {
				var_48 = *(int8_t *)(var_8 + (var_C << 0x6) + var_10) & 0xff;
			}
			mvprintw(var_44, var_40, "%02x");
			wattr_off(**_stdscr, var_24, 0x0);
		}
	}
	return;
}

int _draw_sep(int arg0) {
	var_4 = arg0;
	wattr_on(**_stdscr, 0x242a00, 0x0);
	for (var_8 = 0x0; var_8 <= 0x43; var_8 = var_8 + 0x1) {
		if (wmove(**_stdscr, var_8, var_4) != 0xffffffff) {
			waddch(**_stdscr, 0x2a);
		}
	}
	rax = wattr_off(**_stdscr, 0x242a00, 0x0);
	return rax;
}

int _draw_line(int arg0) {
	var_4 = arg0;
	wattr_on(**_stdscr, 0x242a00, 0x0);
	for (var_8 = 0x0; var_8 < 0xfd; var_8 = var_8 + 0x1) {
		if (wmove(**_stdscr, var_4, var_8) != 0xffffffff) {
			waddch(**_stdscr, 0x2a);
		}
	}
	rax = wattr_off(**_stdscr, 0x242a00, 0x0);
	return rax;
}