/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/gui/notify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/30 11:03:40 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

int	vm_guinotify(uint16_t i, int color, int attrs, uint8_t lt)
{
	if (!g_vm->opt.g)
		return (YEP);
	if (color >= 0)
		g_map[i].color = (uint8_t)color;
	g_map[i].attrs = (uint8_t)attrs;
	g_map[i].lifetime = lt;
	g_map[i].print = 0;
	return (YEP);
}
