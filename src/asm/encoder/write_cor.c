/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 00:19:15 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/14 05:21:09 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** todo
*/

#include "asm_encoder.h"

/*
** open
*/
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/*
** write
*/
#include <unistd.h>

/*
** close
*/
# include <unistd.h>

/* static t_word	swap_word(t_word w) */
/* { */
/* 	return ((w >> 8) | (w << 8)); */
/* } */

//TODO: use that somewhere in asm_encoder.c
static t_dword	swap_dword(t_dword d)
{
	return ((d & 0x000000ff) << 24
			| (d & 0x0000ff00) << 8
			| (d & 0x00ff0000) >> 8
			| (d & 0xff000000) >> 24);
}

static void		add_header(t_header *header)
{
	t_byte	*header_ptr;
	uint8_t	size;

	header->magic = swap_dword(COREWAR_EXEC_MAGIC);
	header->prog_size = swap_dword(g_cor->length);
	size = (uint8_t)sizeof(t_header);
	header_ptr = (t_byte *)header + size - 1;
	while (size--)
		ft_arrpush(g_cor, (void *)(t_ulong)*header_ptr--, 0); //TODO: ok this is ugly, soooorry
}

static char		*get_output_name(char *filename)
{
	char	*outname;
	size_t	len;

	len = ft_strlen(filename) + 3;
	outname = malloc(len);
    if (!outname)
        return (NULL);
	ft_memcpy(outname, filename, len - 4);
	ft_memcpy(outname +  len - 4, "cor", 3); //TODO: do not hardcode "cor"

	return (outname);
}

void			write_cor(char *filename, t_header *header)
{
	char	*outname;

	outname = get_output_name(filename);
	if (!outname || (g_fd = open(outname, O_WRONLY)) == -1)
		error(E_OPEN, outname);

	add_header(header);
	if (write(g_fd, g_cor->ptr, g_cor->length) == -1)
		error(E_WRITE, outname);

	if (close(g_fd) == -1)
		error(E_CLOSE, outname);

	ft_memdel((void *)&outname);
}
