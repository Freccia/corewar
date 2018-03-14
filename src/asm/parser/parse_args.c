/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 20:43:23 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/14 05:28:07 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** todo
*/

#include "asm_parser.h"

/* // <--- DEBUG */
/* static void			debug_type(t_arg_type type) */
/* { */
/* 	if (type & T_REG) */
/* 		ft_debugstr("type", "T_REG"); */
/* 	if (type & T_DIR) */
/* 		ft_debugstr("type", "T_DIR"); */
/* 	if (type & T_IND) */
/* 		ft_debugstr("type", "T_IND"); */
/* 	if (type & T_LAB) */
/* 		ft_debugstr("type", "T_LAB"); */
/* 	ft_putendl("-"); */
/* } */
/* // DEBUG ---> */

static uint8_t		parse_arg_length(t_arg_type arg_type, t_byte op_code)
{
	if (arg_type & T_REG)
		return (sizeof(t_byte));
	else if ((arg_type & T_IND) || (arg_type && (op_code >= 9 && op_code <= 15)))
		return (sizeof(t_word)); //TODO: if "blabla index", then it's just a word?
	else if (arg_type & T_DIR)
		return (sizeof(t_dword));

	return (0);
}

static t_arg_type	parse_arg_type(char *arg)
{
	int			i;
	t_arg_type	ret;

	ret = T_IND;
	if (*arg == 'r')
	{
		i = ft_atoi(++arg);
		if (i < 1 || i > REG_NUMBER)
			error(E_INVALID, "Invalid register (REG_NUMBER not in range).");
		ret = T_REG;
	}
	else if (*arg == DIRECT_CHAR && ++arg)
		ret = T_DIR;

	if (*arg == LABEL_CHAR && ret != T_REG)
		return (T_LAB | ret); //TODO: check if label exists, eventually after...
	while (*arg)
		if (!ft_isdigit(*arg++))
			error(E_INVALID, "Invalid arg (not a number).");
	return (ret);
}

void				parse_args(t_instruct_read *instruct_r, \
							   t_instruct_parsed *instruct_p)
{
	int	i;

	if ((uint8_t)instruct_r->argc != instruct_p->op->param_nb)
		error(E_INVALID, "Invalid arg (wrong number).");
	if (!instruct_r->argc)
		return ;

	i = 0;
	while (i < instruct_r->argc)
	{
		*(instruct_p->arg_type + i) = parse_arg_type(*(instruct_r->argv + i));

		*(instruct_p->arg_length + i) = \
			parse_arg_length(*(instruct_p->arg_type + i), instruct_p->op->op_code);

		/* debug_type(*(instruct_p->arg_type + i));			/\* DEBUG *\/ */

		if ((!(*(instruct_p->arg_type + i) & ~T_LAB)) &	\
				*(instruct_p->op->param_type + i))
			error(E_INVALID, "Invalid arg (wrong arg type).");

		i++;
	}
}
