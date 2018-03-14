/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hdelone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 17:40:37 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/18 23:28:43 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** delete the node corresponding to 'key' from the table
** (using table->key_del and table->value_del if non-null)
*/

#include "libft/hsh.h"

static void	del_node(t_htable *table, t_hnode *node)
{
	if (table->key_del)
		table->key_del(node->key, table->key_size);
	if (table->value_del)
		table->value_del(node->value, table->value_size);
	ft_memdel((void *)&node);
	table->length--;
}

void		ft_hdelone(t_htable *table, void *key)
{
	t_hnode	*node;
	t_hnode	*prev;
	t_hnode	**first;
	size_t	hash;

	hash = table->hash(key, table->key_size);
	first = table->bucket + hash % table->bucket_size;
	node = *first;
	prev = NULL;
	while (node)
	{
		if (hash == node->hash && \
				!table->key_cmp(&key, &node->key, table->key_size))
		{
			if (prev)
				prev->next = node->next;
			else
				*first = NULL;
			del_node(table, node);
			return ;
		}
		prev = node;
		node = node->next;
	}
}
