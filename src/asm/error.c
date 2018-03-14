/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 03:39:12 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/14 04:29:44 by mc               ###   ########.fr       */
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
# include <unistd.h>

/*
** I'm pretty sure there is another way...
*/
static int		get_index(uint8_t flag)
{
	int		index;

	index = 0;
	while ((flag /= 2))
		index++;
	return (index - 1);
}

static int      fail(char const *s)
{
    return (write(2, s, ft_strlen(s)));
}

static int      failn(char const *s)
{
    return (fail(s) + write(2, "\n", 1));
}

t_bool			error(uint8_t flag, char *msg)
{
	const char	*error[] = {
		" [-dump NBR_CYCLES] [[-n NUMBER] FILE.cor]...",
		" FILE.s",
		": Ouch... can't read this.",
		": Damn! Can't open file: ",
		": Dang. Can't close file: ",
		": What the heck is that file? Nah, just try with something else. - ",
		": Ooops! Can't write to file: ",
	};

	if (flag & E_USAGE_COREWAR || flag & E_USAGE_ASM)
		fail("Usage: ");
	fail(g_exec_name);
	if (msg)
	{
		fail(error[get_index(flag & (uint8_t)~E_NOEXIT)]);
		failn(msg);
	}
	else
		failn(error[get_index(flag & (uint8_t)~E_NOEXIT)]);
	if (g_fd != -1)
		close(g_fd);
	if (!(flag & E_NOEXIT))
		exit(EXIT_FAILURE);
	return (FALSE);
}
