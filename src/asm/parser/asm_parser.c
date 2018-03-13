/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 14:24:52 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/19 20:43:49 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** -store label as key in labels, with value = cor.len
** -push op in cor
** -push arg-type in cor
** -push argv.len empty bytes in cor
** -if label in argv:
** 	-recurse to read_loop()
** -ninja-copy argv in cor
*/

#include "asm_parser.h"

static t_op		*parse_op(char *op, t_instruct_parsed *instruct_p)
{
	t_op	*op_tab_swap;

	op_tab_swap = op_tab;
	while (op_tab_swap->name && ft_strcmp(op_tab_swap->name, op))
		op_tab_swap++;
	if (!op_tab_swap->name)
		error(E_INVALID, "Invalid op (not found).");

	instruct_p->op = op_tab_swap;
	ft_arrpush(g_cor, (void *)(t_ulong)op_tab_swap->code, -1);
	return (op_tab_swap);
}

static void		parse_label(char *label, t_dword addr)
{
	if (!*label)
		return ;
	if (ft_hget(g_labels, label))
		error(E_INVALID, "Invalid label (appears twice).");
	ft_hset(g_labels, ft_strdup(label), (void *)(t_ulong)addr);
}

void			parse_instruct(t_instruct_read *instruct_r)
{
	t_instruct_parsed	instruct_p;

	if (g_cor->length > CHAMP_MAX_SIZE)
		error(E_INVALID, "Invalid champion (too big).");

	ft_bzero(&instruct_p, sizeof(t_instruct_parsed));
	instruct_p.addr = g_cor->length;

	parse_label(instruct_r->label, g_cor->length);
	if (*instruct_r->op)
	{
		parse_op(instruct_r->op, &instruct_p);
		parse_args(instruct_r, &instruct_p);
		encode(instruct_r, &instruct_p);
	}
}
