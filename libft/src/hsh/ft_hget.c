/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hget.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 17:26:07 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/18 23:44:15 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** return the value corresponding to 'key' in the hash table
** (using table->key_cmp)
*/

#include "libft/hsh.h"

void		*ft_hget(t_htable *table, void *key)
{
	t_hnode	*node;
	size_t	hash;

	hash = table->hash(key, table->key_size);
	node = *(table->bucket + hash % table->bucket_size);
	while (node)
	{
		if (hash == node->hash && \
				!table->key_cmp(&key, &node->key, table->key_size))
			return (node->value);
		node = node->next;
	}
	return (NULL);
}
