/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 00:13:51 by mcanal            #+#    #+#             */
/*   Updated: 2016/05/21 10:51:23 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** return the element at the specified index
** negative index allowed! (-1 == end)
*/

#include "libft/arr.h"

void			*ft_arrget(t_arr *arr, int index)
{
	if (!arr->length)
		return (NULL);
	if (index < 0)
		index += (int)arr->length;
	if (index < 0 || index >= (int)arr->length)
		index = (int)arr->length - 1;
	return ((void *)
			((t_uchar *)arr->ptr + ((size_t)index * arr->sizeof_element)));
}
