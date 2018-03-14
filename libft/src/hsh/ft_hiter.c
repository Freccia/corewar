/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hiter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 10:28:57 by mcanal            #+#    #+#             */
/*   Updated: 2016/05/24 11:12:29 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** apply f to each node
** (this is NOT a nazi function!)
*/

#include "libft/hsh.h"

void		ft_hiter(t_htable *table, void (*f)(t_hnode *node))
{
	t_hnode	**bucket;
	size_t	bucket_size;
	t_hnode	*node;

	bucket = table->bucket;
	bucket_size = table->bucket_size;
	while (bucket_size--)
	{
		if (*bucket)
		{
			node = *bucket;
			while (node)
			{
				f(node);
				node = node->next;
			}
		}
		bucket++;
	}
}
