/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:03:55 by abetemps          #+#    #+#             */
/*   Updated: 2025/11/30 11:50:22 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <ncurses.h>

static bool	is_wall(unsigned char c)
{
	if (c == WALL1 || c == WALL2 || c == WALL3 || c == WALL4
		|| c == WALL5 || c == WALL6 || c == WALL7 || c == WALL8)
		return (1);
	return (0);
}

static int	update_projectile(t_game *game, t_projectile *proj, unsigned short *active_proj)
{
	if (proj->y + proj->y_dir < 0 || proj->y + proj->y_dir > game->board_height
		|| proj->x + proj->x_dir < 0 || proj->x + proj->x_dir > game->board_width)
	{
		proj->active = false;
		--(*active_proj);
		return (1);
	}
	else if (is_wall(game->board[proj->y + proj->y_dir][proj->x + proj->x_dir]))
	{
		proj->active = false;
		game->board[proj->y][proj->x] = GROUND;
		--(*active_proj);
		return (2);
	}
	else if (game->board[proj->y + proj->y_dir][proj->x + proj->x_dir] == HERO)
	{
		game->entities[0].alive = false;
		proj->active = false;
		--(*active_proj);
		return (3);
	}
	if (game->board[proj->y][proj->x] != HERO
		&& game->board[proj->y][proj->x] != ENEMY1
		&& game->board[proj->y][proj->x] != ENEMY2
		&& game->board[proj->y][proj->x] != ENEMY3
		&& game->board[proj->y][proj->x] != BOSS_LEFT
		&& game->board[proj->y][proj->x] != BOSS_RIGHT)
		game->board[proj->y][proj->x] = GROUND;
	proj->x += proj->x_dir;
	proj->y += proj->y_dir;
	game->board[proj->y][proj->x] = HERO_PROJ;
	
	return (0);
}

extern void	update_projectiles(t_game *game, int frame)
{
	int hit = 0;
	(void)hit;

	if (frame % 2)
		return;
	for (int i = 0; i < game->ent_qty; ++i)
	{
		for (int j = 0; j < MAX_PROJECTILES; ++j)
		{
			if (game->entities[i].projectiles[j].active)
				hit = update_projectile(game, &(game->entities[i].projectiles[j]), &(game->entities[i].active_proj_qty));
		}
	}
}
