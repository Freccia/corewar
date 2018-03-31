/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 20:43:23 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/31 16:57:22 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

/*
** return the argument length (after encoding) based on its arg_type
*/

static t_byte		parse_arg_length(t_arg_type arg_type, int direct_size)
{
	if (arg_type & T_REG)
		return (sizeof(t_byte));
	else if (arg_type & T_IND)
		return (sizeof(t_word));
	else if (arg_type & T_DIR)
		return (direct_size ? sizeof(t_word) : sizeof(t_dword));
	return (0);
}

/*
** return the argument type (T_REG/T_IND/T_DIR/T_LAB) flag
*/

static t_arg_type	parse_arg_type(char *arg)
{
	int			i;
	t_arg_type	ret;

	ret = T_IND;
	if (*arg == 'r')
	{
		i = fatal_atoi(++arg);
		if (i < 1 || i > REG_NUMBER)
			error(E_INVALID, "Invalid register (REG_NUMBER not in range).");
		ret = T_REG;
	}
	else if (*arg == DIRECT_CHAR && ++arg)
		ret = T_DIR;
	if (*arg == LABEL_CHAR && ret != T_REG)
		return (T_LAB | ret);
	if (*arg == '-' && ft_isdigit(*(arg + 1)))
		arg++;
	while (*arg)
		if (!ft_isdigit(*arg++))
			error(E_INVALID, "Invalid arg (not a number).");
	return (ret);
}

/*
** parse the arguments following an op token
*/

void				parse_args(t_instruct_read *instruct_r, \
							t_instruct_parsed *instruct_p)
{
	int	i;

	if ((t_byte)instruct_r->argc != instruct_p->op->param_nb)
		error(E_INVALID, "Invalid arg (wrong number).");
	if (!instruct_r->argc)
		return ;
	i = 0;
	while (i < instruct_r->argc)
	{
		*(instruct_p->arg_type + i) = parse_arg_type(*(instruct_r->argv + i));
		*(instruct_p->arg_length + i) = \
			parse_arg_length(*(instruct_p->arg_type + i), \
							instruct_p->op->direct_size);
		if ((!(*(instruct_p->op->param_type + i) \
				& *(instruct_p->arg_type + i) & ~T_LAB)))
			error(E_INVALID, "Invalid arg (wrong arg type).");
		i++;
	}
}
