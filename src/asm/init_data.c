/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 20:49:51 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/24 20:09:01 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** free
*/
#include <stdlib.h>

t_error_report			g_err;
t_arr					*g_cor = NULL;
t_htable				*g_labels = NULL;


/*
** this will be used to delete the labels names in the hash table
*/
static void			free_string(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

/*
** this will be used to compare the labels names in the hash table
*/
static int			cmp_string(const void *a, const void *b, size_t n)
{
	(void)n;
	return (ft_strcmp(*(char **)a, *(char **)b));
}

/*
** this will be used as our (string) hash algorithm
*/
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

/*
** init the label hash table (char * -> dword)
** and the cor dynamic array (byte[])
*/
void				init_data(void)
{
	g_cor = ft_arrnew(0, sizeof(t_byte));
	g_labels = ft_hnew(0);
	g_labels->value_size = sizeof(t_dword);
	g_labels->key_del = free_string;
	g_labels->key_cmp = cmp_string;
	g_labels->hash = jenkins_hash_str;
}

/*
** init the label hash table and the cor dynamic array
*/
void				init_error_report(char *exec_name)
{
	ft_bzero(&g_err, sizeof(t_error_report));
	g_err.exec_name = exec_name;
	g_err.fd = -1;
}
