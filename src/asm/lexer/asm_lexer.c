/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 22:30:58 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/13 22:04:47 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** todo
*/

#include "asm_lexer.h"

/*
** open
*/
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/*
** close
*/
# include <unistd.h>

/* // <--- DEBUG */
/* static void				debug_header(t_header *header) */
/* { */
/* 	ft_debugnbr("magic", (int)header->magic); */
/* 	ft_debugstr(NAME_CMD_STRING, header->prog_name); */
/* 	ft_debugnbr("prog_size", (int)header->prog_size); */
/* 	ft_debugstr(COMMENT_CMD_STRING, header->comment); */
/* 	/\* ft_putendl(""); *\/ */
/* } */

/* #include <stdio.h> */
/* static void				debug_cor() */
/* { */
/* 	ft_debugnbr("cor.length", (int)g_cor->length); */
/* 	ft_debugnbr("cor.alloc_len", (int)g_cor->alloc_len); */
/* 	for (size_t i = 0; i < g_cor->length; i++) */
/* 		printf("0x%x ", *(t_byte *)ft_arrget(g_cor, i)); */
/* 	fflush(stdout); */
/* 	ft_putendl(g_cor->length ? "\n" : ""); */
/* } */

/* static void				debug_hnode(t_hnode *node) */
/* { */
/* 	ft_debugstr("labels.key", (char *)node->key); */
/* 	ft_debugnbr("labels.value", (int)node->value); */
/* } */

/* static void				debug_labels() */
/* { */
/* 	ft_debugnbr("labels.length", (int)g_labels->length); */
/* 	ft_hiter(g_labels, debug_hnode); */
/* 	ft_putendl(""); */
/* } */
/* // DEBUG ---> */

static void				check_filename(char *filename)
{
	size_t		len;

	len = ft_strlen(filename);
	if (len < 3 || ft_strcmp(".s", filename + len - 2))
		error(E_INVALID, "Invalid file name.");
}

void					lex(char *filename)
{
	t_header	header;

	check_filename(filename);
	if ((g_fd = open(filename, O_RDONLY)) == -1)
		error(E_OPEN, filename);

	ft_bzero(&header, sizeof(t_header));
	read_header(&header);
	/* debug_header(&header);		/\* DEBUG *\/ */

	init_data();
	read_loop();
	/* debug_cor();	/\* DEBUG *\/ */
	/* debug_labels();	/\* DEBUG *\/ */

	ft_hdel(&g_labels);
	if (close(g_fd) == -1)
		error(E_CLOSE, filename);

	write_cor(filename, &header);
	/* debug_cor();	/\* DEBUG *\/ */
	ft_arrdel(&g_cor);
}
