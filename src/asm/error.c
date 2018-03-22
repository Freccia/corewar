/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 03:39:12 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/23 00:30:06 by mc               ###   ########.fr       */
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

/*
** I'm pretty sure there is another way
*/
static int		get_index(uint8_t flag)
{
	int		index;

	index = 0;
	while ((flag /= 2))
		index++;
	return (index - 1);
}

static int		fail(char const *s)
{
	return (s ? (int)write(2, s, ft_strlen(s)) : 0);
}

static int		failn(char const *s)
{
	return (fail(s) + (int)write(2, "\n", 1));
}

//TODO: use ft_fprintf for all these
static void		pretty_error(char *error_type)
{
	char *line_pos;

	fail(CLR_WHITE);
	fail(g_err.file_name);
	fail(":");
	line_pos = ft_itoa(g_err.line_pos, 10);
	fail(line_pos);
	free(line_pos);
	/* fail(":"); */
	/* fail(col_pos); */
	fail(": ");
	fail(CLR_RED);
	fail(error_type);
	failn(CLR_RESET);
	if (g_err.line)
	{
		failn(g_err.line);
		failn("\t" CLR_GREEN "^" CLR_RESET); //TODO: handle col_pos
	}
	failn("");
}

t_bool			error(uint8_t flag, char *msg)
{
	const char	*error[] = {
		" FILE.s",
		": Ouch... can't read this.",
		": Damn! Can't open file: ",
		": Dang. Can't close file: ",
		": Ooops! Can't write to file: ",
	};

	if (flag & E_USAGE_ASM)
		fail("Usage: ");
	if (!(flag & E_INVALID))
		fail(g_err.exec_name);
	if (msg)
	{
		if (flag & E_INVALID)
			pretty_error(msg);
		else
		{
			fail(error[get_index(flag & (uint8_t)~E_NOEXIT)]);
			failn(msg);
		}
	}
	else
		failn(error[get_index(flag & (uint8_t)~E_NOEXIT)]);
	if (!(flag & E_NOEXIT))
		exit(EXIT_FAILURE);
	return (FALSE);
}
