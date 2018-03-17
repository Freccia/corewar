/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/17 19:46:26 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "libft/buf.h"
# include "libft/cty.h"
# include "libft/ds.h"
# include "libft/ex.h"
# include "libft/fs.h"
# include "libft/ft_glob.h"
# include "libft/hash.h"
# include "libft/int.h"
# include "libft/io.h"
# include "libft/lib.h"
# include "libft/math.h"
# include "libft/mem.h"
# include "libft/str.h"
# include "libft/tys.h"
# include "libft/sort.h"
# include "libft/getopt.h"
# include "libft/hsh.h"
# include "libft/arr.h"

void			ft_print_memory(const void *addr, size_t size);
size_t			ft_mtoi(const unsigned char *mem, size_t len);
int32_t			ft_32npow(const int32_t nb, int power);

#endif
