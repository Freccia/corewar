/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hdel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 16:02:41 by mcanal            #+#    #+#             */
/*   Updated: 2016/05/24 00:14:32 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** delete the whole hash table
** (using table->key_del and table->value_del if non-null)
*/

#include "libft/hsh.h"

static void		del_list(t_htable *table, t_hnode *node)
{
	t_hnode	*next;

	while (node)
	{
		next = node->next;
		if (table->key_del)
			table->key_del(node->key, table->key_size);
		if (table->value_del)
			table->value_del(node->value, table->value_size);
		ft_memdel((void *)&node);
		node = next;
	}
}

void			ft_hdel(t_htable **table)
{
	t_hnode	**bucket;

	bucket = (*table)->bucket;
	while ((*table)->bucket_size--)
	{
		if (*bucket)
			del_list(*table, *bucket);
		bucket++;
	}
	ft_memdel((void *)&(*table)->bucket);
	ft_memdel((void *)table);
}
