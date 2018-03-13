/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 13:23:15 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/13 21:45:51 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H

# define UTIL_H

# include "libft.h"

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif


/*
** error code enum
*/
enum					e_error
{
	E_NOERROR = 0,
	E_NOEXIT = (1 << 0),
	E_USAGE_COREWAR = (1 << 1),
	E_USAGE_ASM = (1 << 2),
	E_READ = (1 << 3),
	E_OPEN = (1 << 4),
	E_CLOSE = (1 << 5),
	E_INVALID = (1 << 6),
	E_WRITE = (1 << 7)
};

typedef unsigned char			t_byte;
typedef unsigned short			t_word;
typedef unsigned int			t_dword;

# define BSWAP_WORD(x) ((t_word) ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8)))

# define BSWAP_DWORD(x) ((((x) & 0xff000000) >> 24) | (((x) & 0x00ff0000) >> 8)	\
						| (((x) & 0x0000ff00) << 8) | (((x) & 0x000000ff) << 24))

/*
** globad
*/
extern char				*g_exec_name;
extern int				g_fd;

/*
** error.c
*/
t_bool					error(uint8_t flag, char *msg);

#endif
