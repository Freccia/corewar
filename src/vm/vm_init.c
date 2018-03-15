/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 10:10:16 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/15 12:00:58 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "corewar.h"

static uint8_t	*g_players[MAX_PLAYERS];
static uint16_t	g_player_lens[MAX_PLAYERS];
static int		g_player_r1[MAX_PLAYERS];
static uint8_t	g_player = 0;

uint16_t		cw_vm_parse(const char *filename, uint8_t *dest)
{
	int		fd;
	ssize_t	bin_size;
	char	buf[4096];
	void	*ptr;

	//ft_printf("filename: %s\n", filename);
	if ((fd = open(filename, O_RDONLY)) < 0)
		cw_exit(3, "Failed opening file.\n");
	if (read(fd, &buf, _CW_HEAD_SZ) < _CW_HEAD_SZ)
		cw_exit(3, "Failed reading file header.\n");
	if (*(unsigned int*)buf != _CW_MAGIC)
		cw_exit(3, "Wrong file: magic number.\n");
	if ((bin_size = read(fd, &buf, CHAMP_MAX_SIZE + 1)) <= 0)
		cw_exit(3, "Failed reading file binary.\n");
	if (bin_size > CHAMP_MAX_SIZE)
		cw_exit(3, "Champion exceeding size: %d\n", bin_size);
	if (close(fd) < 0)
		cw_exit(3, "Failed closing fd.\n");
	ft_memcpy(dest, buf, (size_t)bin_size);
	ptr = (void*)&(g_cw->champs[g_player].name);
	ft_memcpy(ptr, dest + sizeof(_CW_MAGIC),
		PROG_NAME_LENGTH);
	g_cw->champs[g_player].id = g_player_r1[g_player];
	return ((uint16_t)bin_size);
}

static int		vm_init(void)
{
	int		plyrs_dist;
	int		i;
	t_proc	*ptr;

	plyrs_dist = MEM_SIZE / g_player;
	i = -1;
	g_cw->cycle_to_die = CYCLE_TO_DIE;
	cw_nc_init();
	while (++i < g_player)
	{
		if (!(ptr = malloc(sizeof(t_proc))))
			return (cw_exit(EXIT_FAILURE, "%m\n"));
		ft_bzero(ptr, sizeof(t_proc));
		ptr->pc = g_cw->mem + (i * plyrs_dist);
		ptr->wait = cw_instr_cycles(*ptr->pc);
		ft_memcpy(ptr->reg[1], g_player_r1 + i, REG_SIZE);
		ptr->color = (uint8_t)(i + 1);
		cw_mem_cpy(ptr->pc, g_players[i], g_player_lens[i], ptr->color);
		++g_cw->proc_count;
		g_cw->procs ? (ptr->next = g_cw->procs) : 0;
		g_cw->procs = ptr;
	}
	g_cw->prev = g_cw->procs;
	g_cw->current = g_cw->procs;
	g_cw->n_champs = g_player;
	return (YEP);
}

static int		r1_checkvalid(int r1)
{
	uint8_t	i;

	if (r1 > UINT16_MAX || r1 < 0)
	{
		errno = EOVERFLOW;
		cw_exit(EXIT_FAILURE, "%d: Invalid champion number: %m\n", r1);
	}
	i = 0;
	while (i < g_player)
	{
		if (g_player_r1[i] == (uint16_t)r1)
			cw_exit(EXIT_FAILURE, "%d: Duplicate champion number\n", r1);
		++i;
	}
	return (r1);
}

int				cw_vm_init(int ac, char **av, int r1)
{
	int		opt;
	uint8_t	buf[MEM_SIZE];
	uint8_t	*ptr;

	ptr = buf;
	while (g_optind < ac)
	{
		if (g_player >= MAX_PLAYERS)
			return (cw_exit(EXIT_FAILURE, "Too much players\n"));
		g_player_r1[g_player] = r1_checkvalid(r1);
		g_player_lens[g_player] = cw_vm_parse(av[g_optind], ptr);
		g_players[g_player] = buf;
		ptr += g_player_lens[g_player];
		if (++g_optind < ac)
		{
			if ((opt = ft_getopt(ac, av, "n:")) == WUT)
				++r1;
			else if (opt != 'n')
				return (cw_exit(EXIT_FAILURE, NULL));
			else
				r1 = (uint16_t)ft_atoi(g_optarg);
		}
		++g_player;
	}
	return (vm_init());
}
