/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:00:22 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/14 18:13:52 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** OP: 0x2
** Transfert direct RAM > Registre. Charge le premier parametre dans le registre
** passé en second parametre. Si la valeur du premier parametre est egale a zero
** alors le carry passe a l'etat un, sinon a l'etat zero.
*/

int					cw_ld(uint8_t a1, uint8_t a2, uint8_t a3)
{
	(void)a1;
	(void)a2;
	(void)a3;
	return (YEP);
}
