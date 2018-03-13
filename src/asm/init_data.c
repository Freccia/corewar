/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 20:49:51 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/19 20:55:44 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** todo
*/

#include "asm.h"

/*
** free
*/
# include <stdlib.h>

t_arr					*g_cor = NULL;
t_htable				*g_labels = NULL;

static void			free_string(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

static int			cmp_string(const void *a, const void *b, size_t n)
{
	(void)n;
	return ft_strcmp(*(char **)a, *(char **)b);
}

static size_t		jenkins_hash_str(const void *content, size_t content_size)
{
	size_t	hash;
	t_uchar	*swap;

	hash = 0;
	swap = (t_uchar *)content;
	content_size = ft_strlen(content);
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

void				init_data(void)
{
	g_cor = ft_arrnew(0, sizeof(t_byte));
	g_labels = ft_hnew(0);
	g_labels->value_size = sizeof(t_dword);
	g_labels->key_del = free_string;
	g_labels->key_cmp = cmp_string;
	g_labels->hash = jenkins_hash_str;
}
