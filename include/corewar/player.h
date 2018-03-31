/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar/player.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/30 11:07:06 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_PLAYER_H
# define COREWAR_PLAYER_H

# include <libft.h>

# include "op.h"

typedef struct		s_player
{
	struct s_player	*next;
	int				id;
	uint8_t			idx;
	const char		name[PROG_NAME_LENGTH + 1];
	const char		comment[COMMENT_LENGTH + 1];
	uint8_t			bin[CHAMP_MAX_SIZE + 1];
	uint32_t		last_live;
	uint32_t		lives_in_period;
	size_t			size;
}					t_player;

typedef struct		s_players
{
	t_player		*head;
	size_t			len;
}					t_players;

/*
** Load a player from `file`. Exit the vm on error.
** @param player   A pointer to a t_player struct to fill.
** @param file     The filename to form player from.
** @param id       The player id (-n option).
*/
void				vm_playerload(t_player *player, const char *file, int id);

/*
** Sort push a player in a simple linked list.
** @param players   The players list.
** @param player    The player to push (Memory is duplicated form).
*/
void				vm_playerspush(t_players *players, t_player *player);

/*
** Try to find a player by `id`.
** @param players   The players list.
** @param id        The id to lookup.
*/
t_player			*vm_playersfind(t_players *players, int id);

/*
** Clear player simple linked list.
** @param players   The players list to clear.
*/
void				vm_playersclr(t_players *players);

#endif
