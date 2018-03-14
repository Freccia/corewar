/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:58:23 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/14 17:33:49 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cw_mem_cpy(uint8_t *mem, uint8_t const *src, size_t len, uint16_t p)
{
	while (len)
	{
		cw_nc_notify((uint16_t)(mem - g_cw->mem), p, *src);
		*mem++ = *src++;
		--len;
	}
}

uint16_t	cw_instr_cycles(uint8_t instr)
{
	static int	instr_cycles[16] = {10, 5, 5, 10, 10, 6, 6, 6, 
		20, 25, 25, 800, 10, 50, 1000, 2};

	return (instr_cycles[instr]);
}
