/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 01:45:46 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/14 05:19:11 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** sort an array using shell_sort (based on arr->cmp)
*/

#include "libft/arr.h"
#include "libft/sort.h"

void			ft_arrsort(t_arr *arr)
{
	ft_shellsort(arr->ptr, arr->length, arr->sizeof_element, arr->cmp);
}
