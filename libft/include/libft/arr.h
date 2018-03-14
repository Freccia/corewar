/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/arr.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 04:41:12 by mc                #+#    #+#             */
/*   Updated: 2018/03/14 04:50:13 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARR_H
# define ARR_H

#include "type.h"

/*
** arr struct - dynamic array
*/
typedef struct s_arr	t_arr;
struct					s_arr
{
	void				*ptr;
	size_t				length;
	size_t				sizeof_element;
	size_t				alloc_len;
	t_ncmp				*cmp;
	t_cpy				*cpy;
	t_del				*del;
};

/*
** arr
*/
t_arr					*ft_arrnew(size_t length, size_t sizeof_element);
t_arr					*ft_arrdup(t_arr *arr);
void					ft_arrdel(t_arr **arr);
void					ft_arrpush(t_arr *arr, void *data, int index);
void					*ft_arrpop(t_arr *arr, int index);
void					*ft_arrget(t_arr *arr, int index);
void					ft_arrswap(t_arr *arr, int i, int j);
t_bool					ft_arrequ(t_arr *arr1, t_arr *arr2);
void					ft_arrsort(t_arr *arr);
void					*ft_arrfind(t_arr *arr, void *data);
void					ft_arrmult(t_arr *arr, size_t factor);
t_bool					ft_arrjoin(t_arr *dest, t_arr *src);
void					ft_arrslice(t_arr *arr, int start, int stop, int slide);

#endif
