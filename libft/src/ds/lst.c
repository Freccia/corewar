/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ds/lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

void	ft_lstctor(t_lst *lst)
{
	ft_bzero(lst, sizeof(t_lst));
	lst->prev = (struct s_node *)lst;
	lst->next = (struct s_node *)lst;
}

t_node	*ft_lstpush(t_lst *lst, t_node *node)
{
	++lst->len;
	return (ft_nodelput((t_node *)lst, node));
}

t_node	*ft_lstusht(t_lst *lst, t_node *node)
{
	++lst->len;
	return (ft_noderput((t_node *)lst, node));
}

t_node	*ft_lstpop(t_lst *lst)
{
	if (!lst->len)
		return (NULL);
	return (ft_nodeulink(lst->prev, lst->prev->prev, lst->prev->next));
}

t_node	*ft_lstsht(t_lst *lst)
{
	if (!lst->len)
		return (NULL);
	return (ft_nodeulink(lst->next, lst->next->prev, lst->next->next));
}
