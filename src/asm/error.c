/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 03:39:12 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/31 18:29:27 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** errors handling
** first arg is a flag including enums e_error (cf .h) (ex: E_OPEN | E_NOEXIT)
** second arg is an optionnal error message
*/

#include "asm.h"

/*
** exit
*/
#include <stdlib.h>

/*
** close
*/
#include <unistd.h>

static int		clean(void)
{
	if (g_cor)
		ft_arrdel(&g_cor);
	if (g_labels)
		ft_hdel(&g_labels);
	if (g_err.line)
		ft_memdel((void **)&g_err.line);
	if (g_err.fd != -1)
		close(g_err.fd);
	return (0);
}

/*
** I'm pretty sure there is another way
*/

static int		get_index(t_byte flag)
{
	int		index;

	index = 0;
	while ((flag /= 2))
		index++;
	return (index - 1);
}

/*
** print a parsing error in clang-style format
*/

static void		pretty_error(char *error_type)
{
	ft_dprintf(2, CLR_WHITE "%s", g_err.file_name);
	if (g_err.line_pos)
		ft_dprintf(2, ":%d", g_err.line_pos);
	ft_dprintf(2, ": " CLR_RED "%s" CLR_RESET "\n", error_type);
	if (g_err.line)
	{
		ft_dprintf(2, "%s\n", g_err.line);
		ft_dprintf(2, "\t" CLR_GREEN "^" CLR_RESET "\n");
	}
}

/*
** just a weird error handling function...
*/

t_bool			error(t_byte flag, char *msg)
{
	const char	*error[] = {
		" FILE.s",
		": Ouch... can't read this.",
		": Damn! Can't open file: ",
		": Dang. Can't close file: ",
		": Ooops! Can't write to file: ",
	};

	if (flag & E_USAGE_ASM)
		ft_dprintf(2, "Usage: ");
	if (!(flag & E_INVALID))
		ft_dprintf(2, g_err.exec_name);
	if (msg)
	{
		if (flag & E_INVALID)
			pretty_error(msg);
		else
			ft_dprintf(2, "%s%s\n", \
					error[get_index(flag & (t_byte)~E_NOEXIT)], msg);
	}
	else
		ft_dprintf(2, "%s\n", error[get_index(flag & (t_byte)~E_NOEXIT)]);
	if (!(flag & E_NOEXIT))
		exit(clean() || EXIT_FAILURE);
	return (FALSE);
}

int				fatal_atoi(char const *str)
{
	int	i;

	i = ft_atoi(str);
	if (errno)
		error(E_INVALID, "Overflow.");
	return (i);
}
