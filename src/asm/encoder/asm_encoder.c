/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_encoder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 22:20:39 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/24 17:14:51 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_encoder.h"
#define BIG_ENOUGH 4095


/*
** reverse endianess and copy the given address ARG to cor
*/
static void				copy_addr(char *arg, \
								  t_byte *cor_swap, \
								  t_byte addr_size, \
								  t_dword current_addr)
{
	void	*ret;
	t_dword	addr;
	t_byte	i;
	char	debug_buf[BIG_ENOUGH + 1];	/* DEBUG */

	if (*arg == DIRECT_CHAR) //TODO: what the difference between {,in}direct except size?
		arg++;

	if (*arg == LABEL_CHAR)
	{
		if (!(ret = ft_hget(g_labels, arg + 1)))
		{
			ft_strcpy(debug_buf, "Invalid arg (label not found): ");
			ft_memcpy(debug_buf + ft_strlen(debug_buf), arg + 1, \
					  ft_strlen(arg) - 1); /* DEBUG */
			*(debug_buf + ft_strlen(debug_buf) + ft_strlen(arg)) = 0; /* DEBUG */
			error(E_INVALID, debug_buf);
		}
		addr = (t_dword)ret - current_addr - 1;
	}
	else
		addr = (t_dword)ft_atoi(arg); //TODO: catch overflow

	cor_swap += addr_size - 1;
	i = 0;
	while (i < addr_size)
		*cor_swap-- = *((t_byte *)&addr + i++);
}


/*
** replace the previously pushed zeros in cor by the arg encoded values
*/
static void				encode_arg(t_instruct_read *instruct_r, \
								   t_instruct_parsed *instruct_p, \
									t_byte *cor_swap)
{
	t_byte	i;
	t_byte	arg_length;

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

/*
** push 'arg_length' zeros into cor
** return false if there is a label, meaning we're gonna recurse
*/
static t_bool			push_empty_args(t_instruct_parsed *instruct_p)
{
	t_byte	i;
	t_byte	arg_length;

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

/* encoded	<->	 (type[0] << 6) | (type[1] << 4) | (type[2] << 2) | type[3] */
/* Avec type: rien=0, registre=1, direct=2, indirect=3 */
/* Et: (arg_type >> 1) + 1	<->	 type */
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

/*
** encode a given instruction
**
** this might call recursively read_loop(),
** to keep an incomplete label on the stack for further completion
*/
void					encode(t_instruct_read *instruct_r, \
							   t_instruct_parsed *instruct_p)
{
	size_t				empty_args_pos;

	ft_arrpush(g_cor, (void *)(t_ulong)instruct_p->op->op_code, -1);
	if (instruct_p->op->param_nb > 1 || instruct_p->op->op_code == 16) // aff
		encode_arg_type(&(instruct_p->arg_type));
	empty_args_pos = g_cor->length;
	if (!push_empty_args(instruct_p))
		read_loop();
	encode_arg(instruct_r, instruct_p, (t_byte *)g_cor->ptr + empty_args_pos);
}
