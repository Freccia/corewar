/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 21:35:08 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/14 05:18:25 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** add src at the end of dest
** after this, src will be empty, but the arr won't be free
*/

#include "libft/arr.h"
#include "libft/mem.h"
#include "libft/str.h"

static size_t		get_new_size(size_t start, size_t stop)
{
	return (start > stop ? start : get_new_size(start * 2, stop));
}

t_bool				ft_arrjoin(t_arr *dest, t_arr *src)
{
	size_t new_size;

	if (dest->sizeof_element != src->sizeof_element)
		return (FALSE);
	new_size = get_new_size(dest->alloc_len, \
				(dest->length + src->length + 1) * dest->sizeof_element);
	if (new_size != dest->alloc_len)
		dest->ptr = ft_realloc(dest->ptr, dest->alloc_len, new_size);
	dest->alloc_len = new_size;
	ft_memcpy((void *)((t_uchar *)\
					dest->ptr + dest->length * dest->sizeof_element), \
				src->ptr, \
				src->length * dest->sizeof_element);
	dest->length += src->length;
	src->length = 0;
	return (TRUE);
}
