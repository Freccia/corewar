/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:10:02 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/15 11:41:38 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_ld(uint8_t *mem)
{
	int		reg;
	int		value;
	uint8_t	*ptr;

	ptr = mem;
	if (ft_mtoi(mem, 1) == (T_DIR | T_REG))
	{
		value = ft_mtoi(mem + 1, 4);
		mem = (mem + 5);// % MEM_SIZE;
	}
	else
	{
		value = ft_mtoi(mem + (ft_mtoi(mem + 1, 2) % MEM_SIZE), 4);
		mem = (mem + 3);// % MEM_SIZE;
	}
	reg = ft_mtoi(mem, 1);
	if (!reg || reg > REG_NUMBER)
		return (EXIT_FAILURE);
	ft_memcpy(g_cw->current->reg[reg], &value, REG_SIZE);
	if (!value)
		g_cw->current->flags |= _CW_CARRY;
	else
		g_cw->current->flags &= ~(_CW_CARRY);
	return (mem - ptr);
}
