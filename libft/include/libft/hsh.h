/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/hsh.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 04:41:12 by mc                #+#    #+#             */
/*   Updated: 2018/03/14 04:55:32 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HSH_H
# define HSH_H

#include "type.h"
#include "str.h"

/*
** hash struct - hash node
*/
typedef struct s_hnode	t_hnode;
struct					s_hnode
{
	void				*key;
	void				*value;
	size_t				hash;
	t_hnode				*next;
};

/*
** hash struct - hash table
*/
typedef struct s_htable	t_htable;
struct					s_htable
{
	size_t				length;
	t_hnode				**bucket;
	size_t				bucket_size;
	t_hash				*hash;
	t_ncmp				*key_cmp;
	t_cpy				*key_cpy;
	t_del				*key_del;
	size_t				key_size;
	t_ncmp				*value_cmp;
	t_cpy				*value_cpy;
	t_del				*value_del;
	size_t				value_size;
};

/*
** hash
*/
t_htable				*ft_hnew(size_t bucket_size);
void					ft_hset(t_htable *table, void *key, void *value);
void					*ft_hget(t_htable *table, void *key);
void					*ft_hfind(t_htable *table, void *value);
void					ft_hiter(t_htable *table, void (*f)(t_hnode *node));
void					ft_hdel(t_htable **table);
void					ft_hdelone(t_htable *table, void *key);

#endif
