/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 10:10:16 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/14 13:35:08 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static int	cw_bin_stat(const char *filename)
{
	struct stat		bin_stat;
	int				bin_size;

	if (stat(filename, &bin_stat) < 0)
		return (-1);
	bin_size = bin_stat.st_size - _CW_HEAD_SZ;
	if (bin_size > CHAMP_MAX_SIZE || bin_size < 0)
		return (-1);
	return (bin_size);
}

t_proc		*cw_vm_parse(uint8_t *mem, const char *filename)
{
	int				fd;
	int				bin_size;
	char			buf[4096];
	t_proc			*proc;

	(void)mem;
	proc = NULL;
	if ((bin_size = cw_bin_stat(filename)) < 0)
		return (NULL);
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);
	if (read(fd, &buf, _CW_HEAD_SZ) < _CW_HEAD_SZ)
		return (NULL);
	if (*(unsigned int*)buf != _CW_MAGIC)
		return (NULL);

	ft_printf("Magic: %x - %x - %x\n", *(unsigned int*)buf, _CW_MAGIC, _CW_HEAD_SZ);

	if (read(fd, &buf, bin_size) <= 0)
		return (NULL);
	ft_memcpy(mem, buf, bin_size);
	if (close(fd) < 0)
		return (NULL);
	proc = malloc(sizeof(t_proc));
	return (proc);
}

int		cw_vm_init(t_cw *cw, int ac, char **av)
{
	int		i;
	int		plyrs_dist;
	int		dist;
	t_proc	*ptr;

	(void)cw;
	(void)ac;
	i = g_optind;
	plyrs_dist = MEM_SIZE / (ac - g_optind);
	dist = 0;
	while (i < ac)
	{
		ft_printf("MEM: %p - %p\n", cw->mem, &(cw->mem[dist * plyrs_dist]));
		if ((ptr = cw_vm_parse(&(cw->mem[dist * plyrs_dist]), av[i])) == NULL)
			return (cw_exit(EXIT_FAILURE, "%s: Failed parsing file.\n", av[i]));
		ptr->next = cw->procs;
		if (cw->procs)
			cw->procs = ptr;
		++dist;
		++i;
	}
	ft_print_memory(&(cw->mem[0]), MEM_SIZE);
	cw_nc_init(cw);
	return (EXIT_SUCCESS);
}
