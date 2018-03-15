/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:30:43 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/15 18:39:43 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "corewar.h"

char	g_champ_files[PROG_NAME_LENGTH];

static int		cw_vm_check_r1(int r1)
{
	uint8_t	i;

	if (r1 > UINT16_MAX || r1 < 0)
	{
		errno = EOVERFLOW;
		cw_exit(EXIT_FAILURE, "%d: Invalid champion number: %m\n", r1);
	}
	i = 0;
	while (i < _CW_N_CHAMPS)
	{
		if (g_cw->champs[_CW_N_CHAMPS].id == (uint16_t)r1)
			cw_exit(EXIT_FAILURE, "%d: Duplicate champion number\n", r1);
		++i;
	}
	return (r1);
}

uint16_t		cw_vm_parse_champ(const char *filename, int r1)
{
	int		fd;
	ssize_t	bin_size;
	char	buf[4096];
	void	*ptr;

	if ((fd = open(filename, O_RDONLY)) < 0)
		cw_exit(3, "Failed opening file.\n");
	if (read(fd, &buf, _CW_HEAD_SZ) < _CW_HEAD_SZ)
		cw_exit(3, "Failed reading file header.\n");
	if (*(unsigned int*)buf != _CW_MAGIC)
		cw_exit(3, "Wrong file: magic number.\n");
	ptr = (void*)&(g_cw->champs[_CW_N_CHAMPS].name);
	ft_memcpy(ptr, buf + sizeof(_CW_MAGIC),
		PROG_NAME_LENGTH);
	if ((bin_size = read(fd, &buf, CHAMP_MAX_SIZE + 1)) <= 0)
		cw_exit(3, "Failed reading file binary.\n");
	if (bin_size > CHAMP_MAX_SIZE)
		cw_exit(3, "Champion exceeding size: %d\n", bin_size);
	if (close(fd) < 0)
		cw_exit(3, "Failed closing fd.\n");
	g_cw->champs[_CW_N_CHAMPS].id = r1;
	g_cw->champs[_CW_N_CHAMPS].size = bin_size;
	ft_memcpy(g_cw->champs[_CW_N_CHAMPS].bin, buf, (size_t)bin_size);
	return ((uint16_t)bin_size);
}

static int		cw_vm_load_champs(void)
{
	int		plyrs_dist;
	int		i;
	t_proc	*ptr;

	plyrs_dist = MEM_SIZE / g_cw->n_champs;
	i = -1;
	g_cw->cycle_to_die = CYCLE_TO_DIE;
	cw_nc_init();
	while (++i < g_cw->n_champs)
	{
		if (!(ptr = malloc(sizeof(t_proc))))
			return (cw_exit(EXIT_FAILURE, "%m\n"));
		ft_bzero(ptr, sizeof(t_proc));
		ptr->color = (uint8_t)(i + 1);
		ptr->pc = g_cw->mem + (i * plyrs_dist);
		ptr->wait = g_op_tab[*ptr->pc].cycles;
		ptr->id = g_cw->champs[i].id;
		ft_memcpy(ptr->reg[1], &(g_cw->champs[i].id), REG_SIZE);
		cw_mem_cpy(ptr->pc, g_cw->champs[i].bin, g_cw->champs[i].size, ptr->color);
		++g_cw->proc_count;
		g_cw->procs ? (ptr->next = g_cw->procs) : 0;
		g_cw->procs = ptr;
	}
	g_cw->prev = g_cw->procs;
	g_cw->current = g_cw->procs;
	return (YEP);
}

int				cw_vm_init(int ac, char **av, int r1)
{
	int		opt;

	r1 = (!r1) ? 1 : r1;
	while (g_optind < ac)
	{
		if (g_cw->n_champs >= MAX_PLAYERS)
			return (cw_exit(EXIT_FAILURE, "Too much players\n"));
		r1 = cw_vm_check_r1(r1);
		cw_vm_parse_champ(av[g_optind], r1);
		if (++g_optind < ac)
		{
			if ((opt = ft_getopt(ac, av, "n:")) == WUT)
				++r1;
			else if (opt != 'n')
				return (cw_exit(EXIT_FAILURE, NULL));
			else
				r1 = (uint16_t)ft_atoi(g_optarg);
		}
		++g_cw->n_champs;
	}
	return (cw_vm_load_champs());
}
