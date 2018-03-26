/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:30:43 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/26 11:24:35 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "corewar.h"

static t_vec		g_vec_null = {NULL, sizeof(t_champ *), 0, 0};
static t_vec		*g_vec = &g_vec_null;

static int				check_r1(int r1)
{
	int		k;

	if (r1 > UINT16_MAX || r1 < 0)
	{
		errno = EOVERFLOW;
		cw_exit(EXIT_FAILURE, "%d: Invalid champion number: %m\n", r1);
	}
	k = -1;
	while (++k < g_cw->n_champs)
		if (g_cw->champs[k]->id == (uint16_t)r1)
			cw_exit(EXIT_FAILURE, "%d: Duplicate champion number\n", r1);
	return (r1);
}

static t_champ			*parse_champ(const char *filename, int r1)
{
	int			fd;
	ssize_t		bin_size;
	t_champ		*new;
	uint8_t		buf[4096];

	if ((fd = open(filename, O_RDONLY)) < 0)
		cw_exit(3, "Failed opening file.\n");
	if (read(fd, &buf, _CW_HEAD_SZ) < _CW_HEAD_SZ)
		cw_exit(3, "Failed reading file header.\n");
	if (*(uint32_t *)buf != swap_uint32(COREWAR_EXEC_MAGIC))
		cw_exit(3, "Wrong file: magic number.\n");
	if ((new = malloc(sizeof(t_champ))) == NULL)
		cw_exit(EXIT_FAILURE, "%m\n");
	ft_bzero(new, sizeof(t_champ));
	ft_memcpy((void*)(new->name), buf + sizeof(uint32_t), PROG_NAME_LENGTH);
	if ((bin_size = read(fd, &buf, CHAMP_MAX_SIZE + 1)) <= 0)
		cw_exit(3, "Failed reading file binary.\n");
	if (bin_size > CHAMP_MAX_SIZE)
		cw_exit(3, "Champion exceeding size: %d\n", bin_size);
	if (close(fd) < 0)
		cw_exit(3, "Failed closing fd.\n");
	new->id = r1;
	new->size = (size_t)bin_size;
	ft_memcpy(new->bin, buf, new->size);
	return (new);
}

static void				load_champs(uint8_t k, uint8_t n)
{
	int			plyrs_dist;
	t_champ		*champ;
	t_proc		*ptr;

	plyrs_dist = MEM_SIZE / g_cw->n_champs;
	g_cw->cycle_to_die = CYCLE_TO_DIE;
	cw_nc_init();
	while (++k < g_cw->n_champs && (champ = g_cw->champs[k]))
	{
		if (!(ptr = ft_memalloc(sizeof(t_proc))))
			cw_exit(EXIT_FAILURE, "%m\n");
		ptr->color = (uint8_t)++n;
		ptr->pc = g_cw->mem + ((n - 1) * plyrs_dist);
		ptr->k = k;
		ptr->id = champ->id;
		ptr->pid = ++g_cw->max_pid;
		ptr->reg[1] = champ->id;
		cw_mem_cpy(ptr->pc, champ->bin, champ->size, ptr->color);
		ptr->wait = g_op_tab[*ptr->pc - 1].cycles;
		++g_cw->proc_count;
		g_cw->procs ? (ptr->next = g_cw->procs) : 0;
		g_cw->procs = ptr;
	}
	g_cw->current = g_cw->procs;
}

static int				sort_champs(t_champ *champs[])
{
	//TODO
	(void)champs;
	return (0);
}

void					cw_vm_init(int ac, char **av, int r1)
{
	int		opt;
	int		id;

	id = 0;
	while (g_optind < ac)
	{
		if (g_cw->n_champs >= MAX_PLAYERS)
			cw_exit(EXIT_FAILURE, "Too much players\n");
		r1 = check_r1(!r1 ? ++id : r1);
		*(t_champ **)ft_vecpush(g_vec) = parse_champ(av[g_optind], r1);
		g_cw->champs = g_vec->buf;
		++g_cw->n_champs;
		r1 = 0;
		if (++g_optind < ac)
		{
			if ((opt = ft_getopt(ac, av, "n:")) == WUT)
				r1 = 0;
			else if (opt != 'n')
				cw_exit(EXIT_FAILURE, NULL);
			else
				r1 = (uint16_t)ft_atoi(g_optarg);
		}
	}
	!g_cw->n_champs ? cw_exit(EXIT_FAILURE, "No players.\n") : 0;
	load_champs(-1, sort_champs(g_cw->champs));
}
