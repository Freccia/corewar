/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 22:30:58 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/15 21:07:58 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** todo
*/

#include "asm_lexer.h"

#ifdef ANNOYING_DEBUG
static void				debug_header(t_header *header)
{
	DEBUGF("magic: %d", (int)header->magic);
	DEBUGF(NAME_CMD_STRING ": %s", header->prog_name);
	DEBUGF("prog_size: %d", (int)header->prog_size);
	DEBUGF(COMMENT_CMD_STRING ": %s", header->comment);
	/* fprintf(stderr, "\n"); */
}

static void				debug_hnode(t_hnode *node)
{
	DEBUGF("labels.key: %s", (char *)node->key);
	DEBUGF("labels.value: %d", (int)node->value);
}

static void				debug_labels()
{
	DEBUGF("labels.length: %d", (int)g_labels->length);
	ft_hiter(g_labels, debug_hnode);
	fprintf(stderr, "\n");
}
#endif	/* DEBUG */


static void				check_filename(char *filename)
{
	size_t		len;

	len = ft_strlen(filename);
	if (len < 3 || ft_strcmp(".s", filename + len - 2))
		error(E_INVALID, "Invalid file name.");
	g_err.file_name = filename;
}

void					lex(char *filename)
{
	t_header	header;

	check_filename(filename);
	if ((g_err.fd = open(filename, O_RDONLY)) == -1)
		error(E_OPEN, filename);

	ft_bzero(&header, sizeof(t_header));
	read_header(&header);
#ifdef ANNOYING_DEBUG
	debug_header(&header);
#endif							/* DEBUG */

	init_data();
	read_loop();
#ifdef ANNOYING_DEBUG
	debug_labels();
#endif							/* DEBUG */

	ft_hdel(&g_labels);
	if (close(g_err.fd) == -1)
		error(E_CLOSE, filename);

	write_cor(filename, &header);
}
