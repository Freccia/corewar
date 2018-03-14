/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 21:08:34 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/14 22:20:41 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>

int32_t			ft_32npow(const int32_t nb, int power)
{
	int32_t		sum;

	if (!power)
		return (1);
	sum = nb;
	while (--power)
		sum *= nb;
	return (sum);
}
