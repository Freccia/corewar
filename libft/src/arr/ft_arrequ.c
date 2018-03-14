/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 01:37:14 by mcanal            #+#    #+#             */
/*   Updated: 2016/05/24 00:21:22 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** compares two t_arr, return true if they are identicals, otherwise false
** (based on arr->cmp)
*/

#include "libft/arr.h"

t_bool		ft_arrequ(t_arr *arr1, t_arr *arr2)
{
	size_t	i;
	t_uchar	*a;
	t_uchar	*b;

	if (arr1->length != arr2->length || arr1->cmp != arr2->cmp \
			|| arr1->sizeof_element != arr2->sizeof_element)
		return (FALSE);
	i = arr1->length;
	a = arr1->ptr;
	b = arr2->ptr;
	while (i--)
	{
		if (arr1->cmp(a, b, arr1->sizeof_element))
			return (FALSE);
		a += arr1->sizeof_element;
		b += arr1->sizeof_element;
	}
	return (TRUE);
}
