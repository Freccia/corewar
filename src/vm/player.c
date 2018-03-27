/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:17:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/25 03:11:06 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "corewar.h"

void		vm_playerload(t_player *player, const char *file, int id)
{
	int		fd;
	ssize_t	bin_size;
	uint8_t	buf[4096];

	if ((fd = open(file, O_RDONLY)) < 0)
		vm_exit(3, "%m\n");
	if (read(fd, &buf, _CW_HEAD_SZ) < _CW_HEAD_SZ)
		vm_exit(3, "Failed reading file header: %m\n");
	if (*(uint32_t *)buf != swap_uint32(COREWAR_EXEC_MAGIC))
		vm_exit(3, "Wrong file: magic number.\n");
	ft_bzero(player, sizeof(t_player));
	ft_memcpy((void*)(player->name), buf + sizeof(uint32_t), PROG_NAME_LENGTH);
	if ((bin_size = read(fd, &buf, CHAMP_MAX_SIZE + 1)) <= 0)
		vm_exit(3, "Failed reading file binary: %m\n");
	if (bin_size > CHAMP_MAX_SIZE)
		vm_exit(3, "Champion exceeding size: %d\n", bin_size);
	if (close(fd) < 0)
		vm_exit(3, "%m\n");
	player->id = id;
	player->size = (size_t)bin_size;
	ft_memcpy(player->bin, buf, player->size);
	player->next = NULL;
}

void		vm_playerspush(t_players *players, t_player *player)
{
	t_player* node;

	player = ft_memdup(player, sizeof(t_player));
	if (!players->head || players->head->id >= player->id)
	{
		player->next = players->head;
		players->head = player;
	}
	else
	{
		node = players->head;
		while (node->next && node->next->id < player->id)
			node = node->next;
		player->next = node->next;
		node->next = player;
	}
	++players->len;
}

t_player	*vm_playersfind(t_players *players, int id)
{
	t_player *player;

	player = players->head;
	while (player)
	{
		if (player->id == id)
			break ;
		player = player->next;
	}
	return (player);
}

void		vm_playersclr(t_players *players)
{
	t_player	*player;
	void		*tmp;

	player = players->head;
	while (player)
	{
		tmp = player->next;
		free(player);
		player = (t_player *)tmp;
	}
	ft_bzero(players, sizeof(t_players));
}