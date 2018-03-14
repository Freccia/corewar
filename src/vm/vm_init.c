/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 10:10:16 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/14 10:36:40 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

t_proc		*cw_vm_parse(t_cw *cw, const char *filename)
{
	int		fd;
	t_proc	*proc;

	(void)cw;
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);
	if (close(fd) < 0)
		return (NULL);
	return (EXIT_SUCCESS);
}

int		cw_vm_init(t_cw *cw, int ac, char **av)
{
	int		i;
	t_proc	*ptr;

	(void)cw;
	(void)ac;
	i = g_optind;
	while (i < ac)
	{
		if ((ptr = cw_vm_parse(cw, av[i])) == NULL)
			return (error("Failed parsing file.", 3));
		ptr->next = cw->procs;
		if (cw->procs)
			cw->procs = ptr;
	}
	return (EXIT_SUCCESS);
}
