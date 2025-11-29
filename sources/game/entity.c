/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:54:35 by abetemps          #+#    #+#             */
/*   Updated: 2025/11/29 18:25:12 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

extern void	move_entity(t_game *game, short which, short move)
{
	unsigned short	pos_x = game->entities[which].x;
	unsigned short	pos_y = game->entities[which].y;

	game->board[pos_y][pos_x] = GROUND;
	if (move == UP)
	{
		game->board[--pos_y][pos_x] = game->entities[which].type;
		--game->entities[which].y;
	}
	else if (move == DOWN)
	{
		game->board[++pos_y][pos_x] = game->entities[which].type;
		++game->entities[which].y;
	}
	else if (move == LEFT)
	{
		game->board[pos_y][--pos_x] = game->entities[which].type;
		--game->entities[which].x;
	}
	else if (move == RIGHT)
	{
		game->board[pos_y][++pos_x] = game->entities[which].type;
		++game->entities[which].x;
	}
}
