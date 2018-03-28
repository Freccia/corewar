/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/27 21:38:44 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_OPT_H
# define COREWAR_OPT_H

# include <libft.h>

# define VM_VERB_LIVES (1 << 0)
# define VM_VERB_CYCLE (1 << 1)
# define VM_VERB_OPERA (1 << 2)
# define VM_VERB_DEATH (1 << 3)
# define VM_VERB_MOVES (1 << 4)

typedef struct		s_opt
{
	uint8_t			v;
	ssize_t			d;
	uint8_t			g : 1;
	uint16_t		ctmo;
}					t_opt;

/*
** TODO: Doc
** @param opt 
** @param ac 
** @param av 
** @return 
*/
int					vm_optparse(t_opt *opt, int ac, char **av);

#endif
