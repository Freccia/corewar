/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar/player.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/26 17:15:36 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_PLAYER_H
# define COREWAR_PLAYER_H

# include <libft.h>

# include "op.h"

typedef struct		s_player
{
	int				id;
	uint8_t			idx;
	const char		name[PROG_NAME_LENGTH + 1];
	uint8_t			bin[CHAMP_MAX_SIZE + 1];
	uint32_t		lastlive;
	size_t			size;
	struct s_player	*next;
}					t_player;

#endif
