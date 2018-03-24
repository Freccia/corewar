/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 00:19:15 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/24 03:51:36 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** todo
*/

#include "asm_encoder.h"

#ifdef ANNOYING_DEBUG
static void		debug_cor()
{
	DEBUGF("cor.length: %d", (int)g_cor->length);
	DEBUGF("cor.alloc_len: %d", (int)g_cor->alloc_len);
	for (size_t i = 0; i < g_cor->length; i++)
		fprintf(stderr, "0x%x ", *(t_byte *)ft_arrget(g_cor, i));
	fprintf(stderr, g_cor->length ? "\n" : "");
}
#endif	/* DEBUG */

static void		add_header(t_header *header)
{
	t_byte	*header_ptr;
	size_t	size;

	header->magic = swap_uint32(COREWAR_EXEC_MAGIC);
	header->prog_size = swap_uint32(g_cor->length);
	size = (size_t)sizeof(t_header);
	header_ptr = (t_byte *)header + size - 1;
	while (size--)
		ft_arrpush(g_cor, (void *)(t_ulong)*header_ptr--, 0);
}

static char		*get_output_name(char *filename)
{
	char	*outname;
	size_t	len;
	size_t	ext_len;

	ext_len = ft_strlen(COR_EXTENSION);
	len = ft_strlen(filename) + ext_len;
	outname = malloc(len);
	if (!outname)
		return (NULL);
	ft_memcpy(outname, filename, len - (ext_len + 1));
	ft_memcpy(outname +	len - (ext_len + 1), COR_EXTENSION, ext_len + 1);
	return (outname);
}

void			write_cor(char *filename, t_header *header)
{
	char	*outname;

	if (!g_cor->length)
		error(E_INVALID, "You must write at least one byte! (don't be lazy)");

	outname = get_output_name(filename);
	if (!outname || (g_err.fd = open(outname, O_CREAT | O_WRONLY, 0644)) == -1)
		error(E_OPEN, outname);

	add_header(header);

	write(1, "Writing output program to ", 26);
	write(1, outname, ft_strlen(outname));
	write(1, "\n", 1);

	if (write(g_err.fd, g_cor->ptr, g_cor->length) == -1)
		error(E_WRITE, outname);

	if (close(g_err.fd) == -1)
		error(E_CLOSE, outname);

#ifdef ANNOYING_DEBUG
	debug_cor();
#endif							/* DEBUG */
	ft_memdel((void *)&outname);
	ft_arrdel(&g_cor);
}
