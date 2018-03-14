/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hfind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 10:30:32 by mcanal            #+#    #+#             */
/*   Updated: 2016/05/24 11:11:56 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** return the key corresponding to 'value' in the hash table
** warning: this method is slow as fuck...
** (using table->value_cmp)
*/

#include "libft/hsh.h"

void		*ft_hfind(t_htable *table, void *value)
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
				if (!table->value_cmp(&value, &node->value, table->value_size))
					return (node->key);
				node = node->next;
			}
		}
		bucket++;
	}
	return (NULL);
}
