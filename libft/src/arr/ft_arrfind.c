/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 20:01:38 by mcanal            #+#    #+#             */
/*   Updated: 2016/03/16 20:44:25 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** find an element with data == *arr (based on arr->cmp)
*/

#include "libft/arr.h"

void			*ft_arrfind(t_arr *arr, void *data)
{
	size_t	i;
	t_uchar	*swap;

	i = arr->length;
	swap = (t_uchar *)arr->ptr;
	while (i--)
	{
		if (!arr->cmp((void *)swap, &data, arr->sizeof_element))
			return ((void *)*(t_uchar **)(void *)swap);
		swap += arr->sizeof_element;
	}
	return (NULL);
}
