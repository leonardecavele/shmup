/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:03:55 by abetemps          #+#    #+#             */
/*   Updated: 2025/11/30 15:56:01 by ldecavel         ###   ########.fr       */
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

static void	handle_hit(t_game *game, int hit, t_projectile *proj)
{
	t_entity *hit_ent = NULL;
	(void)hit_ent;
	(void)proj;
	switch (hit)
	{
		case (HERO_HIT):
			--game->entities[0].hp;
			if (game->entities[0].hp <= 0)
			{
				game->board[game->entities[0].y][game->entities[0].x] = DEAD;
			}
			break;
		case (BOSS_HIT):
			--game->entities[1].hp;
			if (game->entities[1].hp == 0)
			{
				game->entities[1].alive = false;
				game->board[game->entities[1].y][game->entities[1].x] = DEAD;
				game->board[game->entities[1].y][game->entities[1].x - 1] = GROUND;
			}
			break;
		case (ENEMY_HIT): // find enemy + handle death
			// hit_ent = find_entity(game->entities, proj->x + proj->x_dir, proj->y + proj->y_dir);
			// --hit_ent->hp;
			// if (hit_ent->hp == 0)
			// {
			// 	hit_ent->alive = false;
			// 	game->board[hit_ent->y][hit_ent->x] = DEAD;
			// }
			break;
	}
}

static int	update_projectile(t_game *game, int i, t_projectile *proj, unsigned short *active_proj, int frame)
{
	if (i != 0 && frame % 3 == 0)
		return (TIME_NO_SHOOT);
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
		return (OUTOFBOUND);
	}
	else if (game->board[ny][nx] == HERO_PROJ
			|| game->board[ny][nx] == ENEMY_PROJ
			|| game->board[ny][nx] == ENEMY1
			|| game->board[ny][nx] == ENEMY2
			|| game->board[ny][nx] == BOSS_LEFT
			|| game->board[ny][nx] == BOSS_RIGHT
			|| game->board[ny][nx] == ENEMY3)
	{
		bool boss_hit = (game->board[ny][nx] == BOSS_LEFT || game->board[ny][nx] == BOSS_RIGHT);
		bool hero_proj = game->board[ny][nx] == HERO_PROJ;
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

		if (boss_hit && hero_proj)
			return (BOSS_HIT);
		else if (hero_proj)
			return (ENEMY_HIT);
		else
			return (NO_HIT);
		// if (game->board[ny][nx] == HERO_PROJ
		// 		|| game->board[ny][nx] == ENEMY_PROJ)
		// 	game->board[ny][nx] = GROUND;
		// if (game->board[proj->y][proj->x] != HERO
		// 		&& game->board[proj->y][proj->x] != ENEMY1
		// 		&& game->board[proj->y][proj->x] != ENEMY2
		// 		&& game->board[proj->y][proj->x] != ENEMY3
		// 		&& game->board[proj->y][proj->x] != BOSS_LEFT
		// 		&& game->board[proj->y][proj->x] != BOSS_RIGHT)
		// 	game->board[proj->y][proj->x] = GROUND;
		// proj->active = false;
		// --(*active_proj);
		// return (ENEMY_HIT);
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
		return (WALL_HIT);
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
		return (HERO_HIT);
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
	return (NO_HIT);
}

extern void	update_projectiles(t_game *game, int frame)
{
	int hit;
	if (frame % 2)
		return;
	for (int i = 0; i < game->ent_qty; ++i)
	{
		for (int j = 0; j < MAX_PROJECTILES; ++j)
		{
			if (game->entities[i].projectiles[j].active)
			{
				hit = update_projectile(game, i, &(game->entities[i].projectiles[j]), &(game->entities[i].active_proj_qty), frame);
				if (hit != NO_HIT && hit != TIME_NO_SHOOT)
					handle_hit(game, hit, &(game->entities[i].projectiles[j]));
			}
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
					tile = ENEMY_PROJ;

				game->board[p->y][p->x] = tile;
			}
		}
	}
}
