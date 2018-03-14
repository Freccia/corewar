/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 19:02:31 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/14 05:11:02 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** push an element into a t_arr
** the right side of the array will be moved consequently
** negative index allowed! (-1 == end)
*/

#include "libft/arr.h"
#include "libft/mem.h"
#include "libft/str.h"

void			ft_arrpush(t_arr *arr, void *data, int index)
{
	t_uchar	*at_index;

	if (index < 0)
		index += (int)arr->length + 1;
	if (!arr->length || index < 0 || index > (int)arr->length)
		index = (int)arr->length;
	if (arr->length >= INT_MAX)
		return ;
	if ((arr->length + 1) * arr->sizeof_element >= arr->alloc_len)
	{
		arr->ptr = ft_realloc(arr->ptr, arr->alloc_len, \
									arr->alloc_len * 2);
		arr->alloc_len *= 2;
	}
	at_index = (t_uchar *)arr->ptr + ((size_t)index * arr->sizeof_element);
	if (arr->length && index != (int)arr->length)
		ft_memmove((void *)(at_index + arr->sizeof_element), (void *)at_index, \
					(arr->length - (size_t)index) * arr->sizeof_element);
	arr->cpy((void *)at_index, &data, arr->sizeof_element);
	arr->length += 1;
}
