/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 14:24:52 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/24 20:29:28 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

/*
** check if an op is defined in the op_tab from op.c
*/
static t_op		*parse_op(char *op, t_instruct_parsed *instruct_p)
{
	t_op	*op_tab_swap;

	op_tab_swap = g_op_tab;
	while ((size_t)(op_tab_swap - g_op_tab) < MAX_OP \
			&& ft_strcmp(op_tab_swap->name, op))
		op_tab_swap++;
	if ((size_t)(op_tab_swap - g_op_tab) == MAX_OP)
		error(E_INVALID, "Invalid op (not found).");

	instruct_p->op = op_tab_swap;
	return (op_tab_swap);
}

/*
** add a label to the hash table (check if it already exists)
*/
static void		parse_label(char *label, t_dword addr)
{
	if (!*label)
		return ;
	if (ft_hget(g_labels, label))
		error(E_INVALID, "Invalid label (appears twice).");
	ft_hset(g_labels, ft_strdup(label), (void *)(t_ulong)addr + 1);
}

/*
** -store label as key in labels, with value = cor.len
** -push op in cor
** -push arg-type in cor
** -push argv.len empty bytes in cor
** -if label in argv:
**	-recurse to read_loop()
** -ninja-copy argv in cor
*/
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
