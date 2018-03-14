/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 00:25:22 by mcanal            #+#    #+#             */
/*   Updated: 2016/05/24 00:18:01 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** free the whole t_arr (using arr->del if non-null)
*/

#include "libft/arr.h"

void		ft_arrdel(t_arr **arr)
{
	t_uchar	*swap;

	if (!*arr)
		return ;
	if ((*arr)->del && (swap = (t_uchar *)(*arr)->ptr))
		while ((*arr)->length--)
		{
			if ((*arr)->del)
				(*arr)->del((void *)swap, (*arr)->sizeof_element);
			swap += (*arr)->sizeof_element;
		}
	ft_memdel((void *)&(*arr)->ptr);
	ft_memdel((void *)arr);
}
