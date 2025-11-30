/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:54:35 by abetemps          #+#    #+#             */
/*   Updated: 2025/11/30 19:19:10 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static bool				is_enemy(unsigned char c)
{
    return (c == ENEMY1 || c == ENEMY2 || c == ENEMY3
        || c == BOSS_LEFT || c == BOSS_RIGHT);
}

extern t_entity			*find_entity(t_entity *entities, short x, short y)
{
	int i = 0;

	while (i < MAX_ENTITY && (entities[i].x != x || entities[i].y != y))
		++i;
	return (&entities[i]);
}


extern void     		move_entity(t_game *game, short which, short move)
{
    unsigned short  pos_x = game->entities[which].x;
    unsigned short  pos_y = game->entities[which].y;

    if ((game->entities[which].type == ENEMY1
         || game->entities[which].type == ENEMY2
         || game->entities[which].type == ENEMY3)
        && !game->entities[which].alive)
    {
        game->board[pos_y][pos_x] = DEAD;
        return;
    }
   if (game->entities[which].type == BOSS_LEFT && !game->entities[which].alive)
    {
        game->board[pos_y][pos_x - 1] = DEAD;
        game->board[pos_y][pos_x] = DEAD;
        return;
    } if (game->entities[which].type == ENEMY1 || game->entities[which].type == ENEMY2 || game->entities[which].type == ENEMY3)
        if (is_enemy(game->board[game->entities[which].y + game->entities[which].y_dir]
			[game->entities[which].x + game->entities[which].x_dir]))
            return ;

    if (move == UP && (game->board[pos_y - 1][pos_x] == GROUND 
				|| (game->board[pos_y - 1][pos_x] == COLLEC && which == 0)))
    {
		if (game->board[pos_y - 1][pos_x] == COLLEC && which == 0)
		{	
			find_collectible(game->collectibles, pos_x, pos_y - 1)->active = false;
			game->score += COLLEC_REWARD;	
		}	
        game->board[pos_y][pos_x] = GROUND;
        game->board[--pos_y][pos_x] = game->entities[which].type;
        --game->entities[which].y;
    }
    else if (move == DOWN && (game->board[pos_y + 1][pos_x] == GROUND
				|| (game->board[pos_y + 1][pos_x] == COLLEC && which == 0)))
    {
		if (game->board[pos_y + 1][pos_x] == COLLEC && which == 0)
		{	
			find_collectible(game->collectibles, pos_x, pos_y + 1)->active = false;
			game->score += COLLEC_REWARD;
		}	
        game->board[pos_y][pos_x] = GROUND;
        game->board[++pos_y][pos_x] = game->entities[which].type;
        ++game->entities[which].y;
    }
    else if (move == LEFT && (game->board[pos_y][pos_x - 1] == GROUND
				|| (game->board[pos_y][pos_x - 1] == COLLEC && which == 0)))
    {
		if (game->board[pos_y][pos_x - 1] == COLLEC && which == 0)
		{	
			find_collectible(game->collectibles, pos_x - 1, pos_y)->active = false;
			game->score += COLLEC_REWARD;
		}	
        game->board[pos_y][pos_x] = GROUND;
        game->board[pos_y][--pos_x] = game->entities[which].type;
        --game->entities[which].x;
    }
    else if (move == RIGHT && (game->board[pos_y][pos_x + 1] == GROUND
				|| (game->board[pos_y][pos_x + 1] == COLLEC && which == 0)))
    {
		if (game->board[pos_y][pos_x + 1] == COLLEC && which == 0)
		{	
			find_collectible(game->collectibles, pos_x + 1, pos_y)->active = false;
			game->score += COLLEC_REWARD;
		}	
        game->board[pos_y][pos_x] = GROUND;
        game->board[pos_y][++pos_x] = game->entities[which].type;
        ++game->entities[which].x;
    }
}
