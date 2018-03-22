/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/22 19:58:15 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int 	main(int ac, char **av)
{
	t_cw	cw;
	int		r1;

	if (ac < 2)
		return (cw_vm_usage(ac, av));
	ft_bzero(&cw, sizeof(t_cw));
	r1 = cw_vm_parse_opt(ac, av, &cw);
	if (cw_vm_init(ac, av, r1))
		return (cw_exit(EXIT_FAILURE, NULL));
	if (cw_vm_run())
		return (cw_exit(EXIT_FAILURE, NULL));
	return (cw_exit(EXIT_SUCCESS, NULL));
}
