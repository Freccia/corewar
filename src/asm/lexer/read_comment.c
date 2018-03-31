/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_comment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 19:55:21 by mc                #+#    #+#             */
/*   Updated: 2018/03/31 03:26:32 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_lexer.h"

static int				check_stuffs_after_quotes(char *line)
{
	while (!IS_EOL(*line))
		if (!ft_isspace(*line++))
			error(E_INVALID, "Invalid header (weird stuffs after quotes).");
	return (TRUE);
}

static size_t			cpy_comment_portion(char *line, \
										t_header *header, size_t comment_len)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	if (line_len + comment_len + 1 > COMMENT_LENGTH)
		error(E_INVALID, "Invalid header (comment too long).");
	ft_memcpy(header->comment + comment_len, line, line_len);
	*(header->comment + comment_len + line_len) = '\n';
	return (line_len + 1);
}

/*
**
** copy multiline comment (relou)
*/

void					read_multiline_comment(char *line, t_header *header)
{
	size_t	comment_len;

	comment_len = cpy_comment_portion(line, header, 0);
	while (TRUE)
	{
		ft_memdel((void **)&(g_err.line));
		if (get_next_line(g_err.fd, &(g_err.line)) <= 0)
			error(E_INVALID, "Invalid header (missing 2nd quote).");
		g_err.line_pos += 1;
		if ((line = ft_strchr(g_err.line, '"')))
		{
			*line = '\0';
			check_stuffs_after_quotes(line + 1);
			comment_len += cpy_comment_portion(g_err.line, header, comment_len);
			*(header->comment + comment_len - 1) = '\0';
			break ;
		}
		comment_len += cpy_comment_portion(g_err.line, header, comment_len);
	}
	ft_memdel((void **)&(g_err.line));
}

/*
**
** helper function to extract string from a pair of double-quotes
*/

void					read_quoted_string(char *line, t_progress *progress)
{
	if (*line != '"')
		error(E_INVALID, "Invalid header (missing 1st quote).");
	++line;
	while (*line && *line != '"')
		line++;
	if (*line != '"')
		*progress |= P_MULTILINE_COMMENT;
	else
	{
		*line = '\0';
		check_stuffs_after_quotes(line + 1);
	}
}
