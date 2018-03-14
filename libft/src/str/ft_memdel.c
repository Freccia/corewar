/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 14:34:47 by mcanal            #+#    #+#             */
/*   Updated: 2014/11/09 22:40:19 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Takes in parameter the address of a pointer whose pointed zone has to be
** freed with free (3), then the pointer is set to NULL.
*/

#include "libft/str.h"
#include <stdlib.h>

void	ft_memdel(void **ap)
{
	if (ap)
	{
		free(*ap);
		*ap = NULL;
	}
}
