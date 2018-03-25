/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:58:23 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/25 22:19:37 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#define BUFF_SIZE 256

void			cw_mem_cpy(uint8_t *dst, uint8_t *src, size_t len, uint16_t p)
{
	while (len--)
	{
		*dst = *src;
		cw_nc_notify((uint16_t)(dst - g_cw->mem), p, *src);
		++src;
		dst = cw_move_ptr(dst, 1);
	}
}

uint8_t			*cw_map_mem(uint8_t *mem, uint8_t *pc, uint16_t n)
{
	uint8_t		k;

	ft_memset(mem, '\0', n * sizeof(uint8_t));
	k = -1;
	while (++k < n)
	{
		mem[k] = *pc;
		pc = cw_move_ptr(pc, 1);
	}
	return (mem);
}

int32_t			cw_read_n(uint8_t *ptr, uint16_t n)
{
	uint8_t		mem[n + 1];

	return (ft_mtoi(cw_map_mem(mem, ptr, n), n));
}

uint8_t			*cw_move_ptr(uint8_t const *pc, int32_t move)
{
	// OK, mais penser a rajouter en fonction de -ctmo
	return (g_cw->mem + ((pc - g_cw->mem + move) % MEM_SIZE));
}

uint32_t		cw_mem_read(uint8_t **ptr, uint8_t *pc, size_t len,
				uint32_t flags)
{
	uint8_t		mem[4];
	uint8_t		*pos;

	if (flags == F_DIR)
		pos = *ptr;
	else if (flags == F_IND_RESTRICT)
		pos = cw_move_ptr(pc, ft_mtoi(cw_map_mem(mem, *ptr, 4), len) % IDX_MOD);
	else
		pos = cw_move_ptr(pc, ft_mtoi(cw_map_mem(mem, *ptr, 4), len));
	*ptr = cw_move_ptr(*ptr, len);
	return (ft_mtoi(cw_map_mem(mem, pos, 4), 4));
}

void	cw_verbose(const t_proc *proc, const char *name, int id, t_verbose flag)
{
	char		s[BUFF_SIZE];

	if (flag == E_VALID_LIVE)
		ft_printf("Player %s [%hd] is alive!\n", name, id);
	else if (flag == E_CYCLE)
		ft_printf("It is now cycle %d\n", g_cw->cycle);
	else if (flag == E_DELTA)
		ft_printf("Cycle to die is now %d\n", g_cw->cycle_to_die);
	else
	{
		ft_snprintf(s, BUFF_SIZE, "Process %d [%s]", proc->num, name);
		if (flag == E_INVALID_LIVE)
			ft_printf("%s made a live... But nobody came.\n", s);
		else if (flag == E_OP)
			ft_printf("%s is executing %s\n", s, g_op_tab[*proc->pc - 1].name);
		else if (flag == E_DEATH)
			ft_printf("%s hasn't lived for %d cycles... Fuck off!", s,\
				g_cw->cycle - proc->lastlive);
//		else if (opt.v & 16 && flag == E_MOVE)
//			ft_printf("%s is moving! ADV %d (%.4p -> %.4p)", s, proc->id, name,\
//				id, 0, 0); TODO proper calc
	}
}
