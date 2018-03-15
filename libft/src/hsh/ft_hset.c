/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 00:16:50 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/15 12:40:55 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** add a new key/value pair in the hash table
** if the key already exists, the value will be overwritten
** the table will automagically resize itself if needed
*/

#include "libft/hsh.h"
#include <stdlib.h>

#define RESIZE_TRIGGER	0.75

static void		move_nodes(t_hnode **bucket, t_hnode *node, size_t bucket_size)
{
	t_hnode	**dst;
	t_hnode	*next;

	while (node)
	{
		next = node->next;
		dst = bucket + node->hash % bucket_size;
		node->next = *dst;
		*dst = node;
		node = next;
	}
}

static size_t	get_new_size(size_t old_size)
{
	size_t			i;
	const size_t	primes[] = {31, 61, 121, 241, 487, 977, 1973, 3947, 7901, \
							15803, 31607, 63241, 126481, 252971, 505949, \
							1011917, 2023837, 4047697, 8095393, 16190789, \
							32381627, 64763263, 129526531, 259053083, \
							518106181, 1036212413, 2072424839};

	if (old_size >= 2072424839)
		return (old_size);
	i = 0;
	while (primes[i] < old_size)
		i++;
	return (primes[i]);
}

static void		resize_table(t_htable *table)
{
	t_hnode	**new_bucket;
	t_hnode	**bucket;
	size_t	size;

	size = table->bucket_size;
	table->bucket_size = get_new_size(size);
	new_bucket = (t_hnode **)\
		ft_memalloc(sizeof(t_hnode *) * table->bucket_size);
	bucket = table->bucket;
	while (size--)
	{
		if (*bucket)
			move_nodes(new_bucket, *bucket, table->bucket_size);
		bucket++;
	}
	free(table->bucket);
	table->bucket = new_bucket;
}

static void		add_node(t_htable *table, void *key, void *value)
{
	size_t	hash;
	t_hnode **bucket_spot;
	t_hnode	*swap;

	hash = table->hash(key, table->key_size);
	bucket_spot = table->bucket + hash % table->bucket_size;
	swap = *bucket_spot;
	while (swap)
	{
		if (hash == swap->hash && \
				!table->key_cmp(&key, &swap->key, table->key_size))
		{
			if (table->value_del)
				table->value_del(swap->value, table->value_size);
			swap->value = value;
			return ;
		}
		swap = swap->next;
	}
	swap = (t_hnode *)ft_memalloc(sizeof(t_hnode));
	table->key_cpy(&swap->key, &key, table->key_size);
	table->value_cpy(&swap->value, &value, table->value_size);
	swap->hash = hash;
	swap->next = *bucket_spot;
	*bucket_spot = swap;
}

void			ft_hset(t_htable *table, void *key, void *value)
{
	add_node(table, key, value);
	table->length++;
	if (table->length / table->bucket_size > RESIZE_TRIGGER)
		resize_table(table);
}
