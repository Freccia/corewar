/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_encoder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 22:20:39 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/13 22:06:19 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** todo
*/

#include "asm_encoder.h"

static void				copy_addr(char *arg, \
								  t_byte *cor_swap, \
								  uint8_t addr_size, \
								  t_dword current_addr)
{
	void	*ret;
	t_dword	addr;
	uint8_t	i;

	if (*arg == DIRECT_CHAR) //TODO: what the difference between {,in}direct except size?
		arg++;

	if (*arg == LABEL_CHAR)
	{
		if (!(ret = ft_hget(g_labels, arg + 1))) //TODO: be sure 0 pass
			error(E_INVALID, "Invalid arg (label not found).");
		addr = (t_dword)ret - current_addr;
	}
	else
		addr = (t_dword)ft_atoi(arg); //TODO: catch > INT_MAX ?

	cor_swap += addr_size - 1;
	i = 0;
	while (i < addr_size)
		*cor_swap-- = *((t_byte *)&addr + i++); //reverse endian-ness
}

static void				encode_arg(t_instruct_read *instruct_r, \
								   t_instruct_parsed *instruct_p, \
									uint8_t empty_args_pos)
{
	uint8_t	i;
	uint8_t	arg_length;
	t_byte	*cor_swap;

	cor_swap = g_cor->ptr + empty_args_pos;
	i = 0;
	while (i < MAX_ARGS_NUMBER && (arg_length = *(instruct_p->arg_length + i)))
	{
		if (arg_length == sizeof(t_byte))
			*cor_swap++ = (t_byte)ft_atoi(*(instruct_r->argv + i) + 1);
		else
		{
			copy_addr(*(instruct_r->argv + i), cor_swap, arg_length, instruct_p->addr);
			cor_swap += arg_length;
		}
		i++;
	}
}

/* return false if there is a label, meaning we're gonna recurse */
static t_bool			push_empty_args(t_instruct_parsed *instruct_p)
{
	uint8_t	i;
	uint8_t	arg_length;

	i = 0;
	while (i < MAX_ARGS_NUMBER && (arg_length = *(instruct_p->arg_length + i)))
	{
		while (arg_length--)
			ft_arrpush(g_cor, (void *)0, -1);
		i++;
	}

	return (!((*instruct_p->arg_type & T_LAB) \
			  || (*(instruct_p->arg_type + 1) & T_LAB) \
			  || (*(instruct_p->arg_type + 2) & T_LAB) \
			  || (*(instruct_p->arg_type + 3) & T_LAB)));
}

/* encoded  <->  (type[0] << 6) | (type[1] << 4) | (type[2] << 2) | type[3] */
/* Avec type: rien=0, registre=1, direct=2, indirect=3 */
/* Et: (arg_type >> 1) + 1  <->  type */
static void				encode_arg_type(t_arg_type (*arg_type)[])
{
	t_byte	encoded_type;

	encoded_type = 0;
	if ((*arg_type)[0] & ~T_LAB)
		encoded_type |= ((((*arg_type)[0] & ~T_LAB) >> 1) + 1) << 6;
	if ((*arg_type)[1] & ~T_LAB)
		encoded_type |= ((((*arg_type)[1] & ~T_LAB) >> 1) + 1) << 4;
	if ((*arg_type)[2] & ~T_LAB)
		encoded_type |= ((((*arg_type)[2] & ~T_LAB) >> 1) + 1) << 2;
	if ((*arg_type)[3] & ~T_LAB)
		encoded_type |= (((*arg_type)[3] & ~T_LAB) >> 1) + 1;

	ft_arrpush(g_cor, (void *)(unsigned long)encoded_type, -1);
}


void					encode(t_instruct_read *instruct_r, \
							   t_instruct_parsed *instruct_p)
{
		uint8_t				empty_args_pos;

		if (instruct_p->op->param_nb > 1 || instruct_p->op->op_code == 16) // aff
			encode_arg_type(&(instruct_p->arg_type));
		empty_args_pos = g_cor->length;
		if (!push_empty_args(instruct_p))
			read_loop();
		encode_arg(instruct_r, instruct_p, empty_args_pos);
}
