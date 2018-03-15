/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/type.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 04:44:08 by mc                #+#    #+#             */
/*   Updated: 2018/03/15 12:39:02 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

/*
** for size_t
*/
# include <string.h>

/*
** for t_bool
*/
# include "tys.h"

# ifndef TRUE
#  define TRUE			1
#  define FALSE			0
# endif

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS	0
#  define EXIT_FAILURE	1
# endif

# ifndef STDIN_FILENO
#  define STDIN_FILENO	0
#  define STDOUT_FILENO	1
#  define STDERR_FILENO	2
# endif

typedef unsigned char	t_uchar;
typedef unsigned short	t_ushort;
typedef unsigned int	t_uint;
typedef unsigned long	t_ulong;
typedef int				t_cmp(const void *a, const void *b);
typedef int				t_ncmp(const void *a, const void *b, size_t n);
typedef void			*t_cpy(void *dest, const void *src, size_t n);
typedef void			t_del(void *content, size_t content_size);
typedef size_t			t_hash(const void *content, size_t content_size);

/*
** eheh
*/
void                    *ft_memalloc(size_t size);
void					ft_memdel(void **ap);
int						get_next_line(int const fd, char **line);

#endif
