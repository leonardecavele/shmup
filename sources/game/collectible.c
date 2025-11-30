/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:57:42 by abetemps          #+#    #+#             */
/*   Updated: 2025/11/30 19:25:51 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"


extern t_collectible	*find_collectible(t_collectible *collec, short x, short y)
{
	int i = 0;

	while (i < MAX_COLLECTIBLES && (collec[i].x != x || collec[i].y != y))
		++i;
	return (&collec[i]);
}

extern void				respawn_collectibles(t_game *game, int seconds)
{
	for (int i = 0; i < game->collec_qty; ++i)
	{
		if (!(seconds % 20) && !game->collectibles[i].active && game->board[game->collectibles[i].y][game->collectibles[i].x] == GROUND)
		{
			game->collectibles[i].active = true;
			game->board[game->collectibles[i].y][game->collectibles[i].x] = COLLEC;
		}
	}
}
