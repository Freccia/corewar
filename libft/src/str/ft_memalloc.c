/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 14:24:25 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/05 21:46:20 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocate (with malloc (3)) and returns a fresh zone of memory. The memory
** allocated is initialized to 0. If the allocation fails,
** the function returns NULL.
*/

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*ptr;

	if (!size)
		size = 1;
	if (!(ptr = malloc(size)))
		return (NULL);
	ft_bzero(ptr, size);
	return (ptr);
}
