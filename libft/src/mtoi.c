/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 10:16:33 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/14 22:20:49 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_mtoi(const unsigned char *mem, size_t len)
{
	int		sum;

	sum = 0;
	while (len)
		sum += (int)*mem++ * ft_32npow(16, (int)(--len * 2));
	return (sum);
}
