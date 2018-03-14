/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:58:23 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/14 16:00:50 by lfabbro          ###   ########.fr       */
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

uint16_t	cw_instr_cycles_bis(uint8_t instr)
{
	if (instr == 0x0a)
		return (25);
	else if (instr == 0x0b)
		return (25);
	else if (instr == 0x0c)
		return (800);
	else if (instr == 0x0d)
		return (10);
	else if (instr == 0x0e)
		return (50);
	else if (instr == 0x0f)
		return (1000);
	else if (instr == 0x10)
		return (2);
	return (0);
}

uint16_t	cw_instr_cycles(uint8_t instr)
{
	if (instr == 0x01)
		return (10);
	else if (instr == 0x02)
		return (5);
	else if (instr == 0x03)
		return (5);
	else if (instr == 0x04)
		return (10);
	else if (instr == 0x05)
		return (10);
	else if (instr == 0x06)
		return (6);
	else if (instr == 0x07)
		return (6);
	else if (instr == 0x08)
		return (6);
	else if (instr == 0x09)
		return (20);
	return (cw_instr_cycles_bis(instr));
}
