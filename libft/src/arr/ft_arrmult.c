/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrmult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 20:49:09 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/14 05:10:36 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** multiplicates the content of the arr (increase size)
** (ie: "foo" * 2 = "foofoo")
** undefined behaviour if factor < 2
*/

#include "libft/arr.h"
#include "libft/mem.h"

static size_t	get_new_size(size_t start, size_t stop)
{
	return (start > stop ? start : get_new_size(start * 2, stop));
}

void			ft_arrmult(t_arr *arr, size_t factor)
{
	size_t	new_size;
	size_t	i;
	t_uchar	*d_swap;
	t_uchar	*s_swap;

	new_size = get_new_size(arr->alloc_len, \
							(arr->length + 1) * arr->sizeof_element * factor);
	if (new_size != arr->alloc_len)
		arr->ptr = ft_realloc(arr->ptr, arr->alloc_len, new_size);
	arr->alloc_len = new_size;
	d_swap = (t_uchar *)arr->ptr + arr->length * arr->sizeof_element;
	new_size = arr->length * factor;
	while (--factor)
	{
		s_swap = (t_uchar *)arr->ptr;
		i = arr->length;
		while (i--)
		{
			arr->cpy((void *)d_swap, (void *)s_swap, arr->sizeof_element);
			s_swap += arr->sizeof_element;
			d_swap += arr->sizeof_element;
		}
	}
	arr->length = new_size;
}
