/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 22:30:58 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/31 16:55:56 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_lexer.h"

/*
** check if the given file name end with the correct asm extension
*/

static void				check_filename(char *filename)
{
	size_t		len;
	size_t		ext_len;

	ext_len = ft_strlen(ASM_EXTENSION);
	g_err.file_name = filename;
	len = ft_strlen(filename);
	if (len < ext_len + 1 || ft_strcmp(ASM_EXTENSION, filename + len - ext_len))
		error(E_INVALID, "Invalid file name.");
}

/*
** start the file lexing
*/

void					lex(char *filename)
{
	t_header	header;

	check_filename(filename);
	if ((g_err.fd = open(filename, O_RDONLY)) == -1)
		error(E_OPEN, filename);
	ft_bzero(&header, sizeof(t_header));
	read_header(&header);
	init_data();
	read_loop();
	ft_hdel(&g_labels);
	if (close(g_err.fd) == -1)
		error(E_CLOSE, filename);
	write_cor(filename, &header);
}
