/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_args.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 15:29:52 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/19 16:47:15 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ARGS_H
# define ARGS_H

typedef enum		e_flag
{
	E_DIR,
	E_IND_LONG,
	E_IND_SHORT
}					t_flag;

typedef	struct		s_args
{
	uint8_t			mask;
	uint8_t			shift;
}					t_args;

#endif
