/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hnew.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 04:59:46 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/14 05:14:51 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** create (with malloc(3)) a new hash table
** if the given bucket_size is null, an arbitrary size will be choosen
** the default table setting aims to store pointers
*/

#include "libft/hsh.h"

static size_t		jenkins_hash(const void *content, size_t content_size)
{
	size_t	hash;
	t_uchar	*swap;

	hash = 0;
	swap = (t_uchar *)content;
	while (content_size--)
	{
		hash += *(swap++);
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	return (hash + (hash << 15));
}

t_htable			*ft_hnew(size_t bucket_size)
{
	t_htable	*new;

	if (!bucket_size)
		bucket_size = 241;
	new = (t_htable *)malloc(sizeof(t_htable));
	new->bucket = (t_hnode **)\
		malloc(sizeof(t_hnode *) * (bucket_size + 1));
	new->bucket_size = bucket_size;
	new->hash = jenkins_hash;
	new->key_cmp = ft_memcmp;
	new->value_cmp = ft_memcmp;
	new->key_cpy = ft_memcpy;
	new->value_cpy = ft_memcpy;
	new->key_size = sizeof(void *);
	new->value_size = sizeof(void *);
	return (new);
}
