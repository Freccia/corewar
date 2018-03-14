/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrslice.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 22:08:23 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/14 05:18:03 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** will remove element outside of the start/stop range (using arr->del)
** use the slide(=step) parameter to skip elements
** (negative index allowed!)
** this is similar to the python slice notation "arr[start:stop:slide]"
*/

#include "libft/arr.h"
#include "libft/str.h"
#include "libft/math.h"

static void		cpy_rev(t_arr *arr, int start, int stop, int slide)
{
	t_uchar	dest[(size_t)((start - stop) / slide + 1) * arr->sizeof_element];
	t_uchar	*s_swap;
	t_uchar	*d_swap;
	int		i;

	s_swap = (t_uchar *)arr->ptr + (arr->length - 1) * arr->sizeof_element;
	d_swap = (t_uchar *)dest;
	i = (int)arr->length;
	while (i--)
	{
		if (i >= start && i <= stop && !((stop - i) % slide))
		{
			ft_memcpy((void *)d_swap, (void *)s_swap, arr->sizeof_element);
			d_swap += arr->sizeof_element;
		}
		else if (arr->del)
			arr->del((void *)s_swap, arr->sizeof_element);
		if (s_swap != (t_uchar *)arr->ptr)
			s_swap -= arr->sizeof_element;
	}
	arr->length = (size_t)(d_swap - dest) / arr->sizeof_element;
	ft_memcpy(arr->ptr, dest, (size_t)(d_swap - dest));
	ft_bzero((void *)((t_uchar *)arr->ptr + (size_t)(d_swap - dest)), \
				arr->alloc_len - (size_t)(d_swap - dest));
}

static void		cpy(t_arr *arr, int start, int stop, int slide)
{
	t_uchar	*s_swap;
	t_uchar	*d_swap;
	int		i;

	s_swap = (t_uchar *)arr->ptr;
	d_swap = (t_uchar *)arr->ptr;
	i = 0;
	while (i < (int)arr->length)
	{
		if (i >= start && i <= stop && !((i - start) % slide))
		{
			ft_memcpy((void *)d_swap, (void *)s_swap, arr->sizeof_element);
			d_swap += arr->sizeof_element;
		}
		else if (arr->del)
			arr->del((void *)s_swap, arr->sizeof_element);
		s_swap += arr->sizeof_element;
		i++;
	}
	arr->length = (size_t)(d_swap - (t_uchar *)arr->ptr) / arr->sizeof_element;
	ft_bzero((void *)d_swap, \
				arr->alloc_len - (size_t)(d_swap - (t_uchar *)arr->ptr));
}

void			ft_arrslice(t_arr *arr, int start, int stop, int slide)
{
	if (!arr->length || !slide)
		return ;
	if (start < 0)
		start += (int)arr->length;
	if (start < 0 || start >= (int)arr->length)
		start = 0;
	if (stop < 0)
		stop += (int)arr->length;
	if (stop < 0 || stop >= (int)arr->length)
		stop = (int)arr->length - 1;
	slide > 0 ? cpy(arr, ft_i32min(start, stop), ft_i32max(start, stop), slide) : \
		cpy_rev(arr, ft_i32min(start, stop), ft_i32max(start, stop), slide);
}
