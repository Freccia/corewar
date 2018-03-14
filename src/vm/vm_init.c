/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 10:10:16 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/14 11:55:05 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

t_proc		*cw_vm_parse(uint8_t *mem, const char *filename)
{
	int				fd;
	struct stat		bin_stat;
	t_proc			*proc;
	char			buf[4096];

	(void)mem;
	proc = NULL;
	if (stat(filename, &bin_stat) < 0)
		return (NULL);

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);
	if (read(fd, &buf, 2180) < 2180)
		return (NULL);
	if (*(unsigned int*)buf != _CW_MAGIC)
		return (NULL);
	ft_printf("Magic: %x - %x\n", *(unsigned int*)buf, _CW_MAGIC);
	if (close(fd) < 0)
		return (NULL);
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
		if ((ptr = cw_vm_parse(&(cw->mem[dist * plyrs_dist]), av[i])) == NULL)
			return (cw_error("Failed parsing file.", 3));
		ptr->next = cw->procs;
		if (cw->procs)
			cw->procs = ptr;
		++dist;
		++i;
	}
	cw_nc_init(cw);
	return (EXIT_SUCCESS);
}
