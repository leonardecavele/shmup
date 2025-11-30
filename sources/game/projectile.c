/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:03:55 by abetemps          #+#    #+#             */
/*   Updated: 2025/11/30 13:52:04 by ldecavel         ###   ########.fr       */
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
	int nx = proj->x + proj->x_dir;
	int ny = proj->y + proj->y_dir;

	if (ny < 0 || ny >= game->board_height
			|| nx < 0 || nx >= game->board_width)
	{
		if (game->board[proj->y][proj->x] != HERO
				&& game->board[proj->y][proj->x] != ENEMY1
				&& game->board[proj->y][proj->x] != ENEMY2
				&& game->board[proj->y][proj->x] != ENEMY3
				&& game->board[proj->y][proj->x] != BOSS_LEFT
				&& game->board[proj->y][proj->x] != BOSS_RIGHT)
			game->board[proj->y][proj->x] = GROUND;
		proj->active = false;
		--(*active_proj);
		return (1);
	}
	else if (game->board[ny][nx] == HERO_PROJ
			|| game->board[ny][nx] == ENEMY_PROJ
			|| game->board[ny][nx] == ENEMY1
			|| game->board[ny][nx] == ENEMY2
			|| game->board[ny][nx] == BOSS_LEFT
			|| game->board[ny][nx] == BOSS_RIGHT
			|| game->board[ny][nx] == ENEMY3)
	{
		if (game->board[ny][nx] == HERO_PROJ
				|| game->board[ny][nx] == ENEMY_PROJ)
			game->board[ny][nx] = GROUND;
		if (game->board[proj->y][proj->x] != HERO
				&& game->board[proj->y][proj->x] != ENEMY1
				&& game->board[proj->y][proj->x] != ENEMY2
				&& game->board[proj->y][proj->x] != ENEMY3
				&& game->board[proj->y][proj->x] != BOSS_LEFT
				&& game->board[proj->y][proj->x] != BOSS_RIGHT)
			game->board[proj->y][proj->x] = GROUND;
		proj->active = false;
		--(*active_proj);
		return (4);
	}
	else if (is_wall(game->board[ny][nx]))
	{
		if (game->board[proj->y][proj->x] != HERO
				&& game->board[proj->y][proj->x] != ENEMY1
				&& game->board[proj->y][proj->x] != ENEMY2
				&& game->board[proj->y][proj->x] != ENEMY3
				&& game->board[proj->y][proj->x] != BOSS_LEFT
				&& game->board[proj->y][proj->x] != BOSS_RIGHT)
			game->board[proj->y][proj->x] = GROUND;
		proj->active = false;
		--(*active_proj);
		return (2);
	}
	else if (game->board[ny][nx] == HERO)
	{
		game->entities[0].alive = false;
		if (game->board[proj->y][proj->x] != HERO
				&& game->board[proj->y][proj->x] != ENEMY1
				&& game->board[proj->y][proj->x] != ENEMY2
				&& game->board[proj->y][proj->x] != ENEMY3
				&& game->board[proj->y][proj->x] != BOSS_LEFT
				&& game->board[proj->y][proj->x] != BOSS_RIGHT)
			game->board[proj->y][proj->x] = GROUND;
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
	proj->x = nx;
	proj->y = ny;
	game->board[proj->y][proj->x] = HERO_PROJ;
	return (0);
}

extern void	update_projectiles(t_game *game, int frame)
{
	if (frame % 2)
		return;
	for (int i = 0; i < game->ent_qty; ++i)
	{
		for (int j = 0; j < MAX_PROJECTILES; ++j)
		{
			if (game->entities[i].projectiles[j].active)
				update_projectile(game, &(game->entities[i].projectiles[j]), &(game->entities[i].active_proj_qty));
		}
	}
	for (int y = 0; y < game->board_height; ++y)
	{
		for (int x = 0; x < game->board_width; ++x)
		{
			if (game->board[y][x] == HERO_PROJ
					|| game->board[y][x] == ENEMY_PROJ)
				game->board[y][x] = GROUND;
		}
	}
	for (int i = 0; i < game->ent_qty; ++i)
	{
		for (int j = 0; j < MAX_PROJECTILES; ++j)
		{
			t_projectile *p = &game->entities[i].projectiles[j];

			if (p->active)
			{
				unsigned char tile;

				if (i == 0)
					tile = HERO_PROJ;
				else
					tile = ENEMY_PROJ; // ennemis + boss

				game->board[p->y][p->x] = tile;
			}
		}
	}
}
