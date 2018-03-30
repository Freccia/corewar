/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/fs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 15:47:15 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FS_H
# define LIBFT_FS_H

# include "io.h"

# ifndef CLR_RESET
#  define CLR_RESET "\033[0m"
# endif
# ifndef CLR_RED
#  define CLR_RED "\033[31;01m"
# endif
# ifndef CLR_WHITE
#  define CLR_WHITE "\033[37;01m"
# endif
# ifndef CLR_BLACK
#  define CLR_BLACK "\033[30;01m"
# endif
# ifndef CLR_YELLOW
#  define CLR_YELLOW "\033[33;01m"
# endif
# ifndef CLR_GREEN
#  define CLR_GREEN "\033[32;01m"
# endif
# ifndef CLR_CYAN
#  define CLR_CYAN "\033[36;01m"
# endif
# ifndef CLR_BOLD
#  define CLR_BOLD "\033[1;01m"
# endif
# ifndef CLR_BRED
#  define CLR_BRED CLR_BOLD"\033[31;01m"
# endif
# ifndef CLR_BYELLOW
#  define CLR_BYELLOW CLR_BOLD"\033[33;01m"
# endif
# ifndef CLR_BCYAN
#  define CLR_BCYAN CLR_BOLD"\033[36;01m"
# endif

extern char	const	*ft_basename(char const *path);
extern t_bool		ft_isdots(char const *path);
extern char			*ft_pathjoin(char const *p1, char const *p2);
extern char			*ft_pathabs(char const *p, char *res, char *to);
extern char			*ft_pathcat(char *dst, char const *src);

#endif
