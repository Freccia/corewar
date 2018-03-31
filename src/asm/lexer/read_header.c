/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 21:43:56 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/31 16:33:21 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** read .name and .comment parts of the .s files
*/

#include "asm_lexer.h"

/*
**
** identifier (.name/.comment) tokenizer
*/

static void				parse_header(char *line,						\
									t_progress progress, t_header *header)
{
	size_t			len;

	if (progress & P_NAME)
	{
		if ((len = ft_strlen(line)) > PROG_NAME_LENGTH)
			error(E_INVALID, "Invalid header (name too long).");
		ft_memcpy(&header->prog_name, line, len);
	}
	else if (progress & P_COMMENT && !(progress & P_MULTILINE_COMMENT))
	{
		if ((len = ft_strlen(line)) > COMMENT_LENGTH)
			error(E_INVALID, "Invalid header (comment too long).");
		ft_memcpy(&header->comment, line, len);
	}
}

/*
**
** identifier (.name/.comment) lexer
*/

static t_progress		read_identifier(char *line)
{
	if (!ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		return (P_NAME);
	if (!ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		return (P_COMMENT);
	error(E_INVALID, "Invalid header (unknown identifier).");
	return (P_NOPROGRESS);
}

/*
**
** lex/parse the current header line
*/

static t_progress		check_header(char *line, t_header *header)
{
	t_progress	progress;

	while (!IS_EOL(*line) && ft_isspace(*line))
		line++;
	if (IS_EOL(*line))
		return (P_NOPROGRESS);
	progress = read_identifier(line);
	while (!IS_EOL(*line) && !ft_isspace(*line))
		line++;
	while (!IS_EOL(*line) && ft_isspace(*line))
		line++;
	read_quoted_string(line, &progress);
	if (progress & P_MULTILINE_COMMENT)
		read_multiline_comment(line + 1, header);
	parse_header(line + 1, progress, header);
	return (progress);
}

/*
**
** read header lines from asm file
*/

void					read_header(t_header *header)
{
	t_progress		progress;

	g_err.line = NULL;
	progress = P_NOPROGRESS;
	while (!(progress & P_NAME && progress & P_COMMENT))
	{
		if (get_next_line(g_err.fd, &(g_err.line)) <= 0)
			error(E_READ, NULL);
		g_err.line_pos += 1;
		progress |= check_header(g_err.line, header);
		ft_memdel((void **)&(g_err.line));
	}
}
