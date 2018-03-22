/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_common.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 18:05:42 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/22 21:01:53 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_COMMON_H
# define CW_COMMON_H

# include <stdint.h>
# include "op.h"

uint32_t	swap_uint32(uint32_t d);

extern t_op			g_op_tab[MAX_OP];

#endif
