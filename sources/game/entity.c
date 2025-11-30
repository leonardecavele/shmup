/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:54:35 by abetemps          #+#    #+#             */
/*   Updated: 2025/11/30 13:25:36 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static bool is_enemy(unsigned char c)
{
    return (c == ENEMY1 || c == ENEMY2 || c == ENEMY3
        || c == BOSS_LEFT || c == BOSS_RIGHT);
}

extern void	move_entity(t_game *game, short which, short move)
{
	unsigned short	pos_x = game->entities[which].x;
	unsigned short	pos_y = game->entities[which].y;

	if (game->entities[which].type == ENEMY1
		|| game->entities[which].type == ENEMY2
		|| game->entities[which].type == ENEMY3)
		if (is_enemy(game->board[game->entities[which].y + game->entities[which].y_dir][game->entities[which].x + game->entities[which].x_dir]))
			return ;

	if (move == UP && game->board[pos_y - 1][pos_x] == GROUND)
	{
		game->board[pos_y][pos_x] = GROUND;
		game->board[--pos_y][pos_x] = game->entities[which].type;
		--game->entities[which].y;
	}
	else if (move == DOWN && game->board[pos_y + 1][pos_x] == GROUND)
	{
		game->board[pos_y][pos_x] = GROUND;
		game->board[++pos_y][pos_x] = game->entities[which].type;
		++game->entities[which].y;
	}
	else if (move == LEFT && game->board[pos_y][pos_x - 1] == GROUND)
	{
		game->board[pos_y][pos_x] = GROUND;
		game->board[pos_y][--pos_x] = game->entities[which].type;
		--game->entities[which].x;
	}
	else if (move == RIGHT && game->board[pos_y][pos_x + 1] == GROUND)
	{
		game->board[pos_y][pos_x] = GROUND;
		game->board[pos_y][++pos_x] = game->entities[which].type;
		++game->entities[which].x;
	}
}
