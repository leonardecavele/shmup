/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 825/11/29 22:13:58 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/30 13:12:24 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"
#include "game.h"

static void	shoot_up(t_entity *enemy, int i)
{
	enemy->projectiles[i].active = true;
	enemy->projectiles[i].x = enemy->x;
	enemy->projectiles[i].y = enemy->y;
	enemy->projectiles[i].x_dir = 0;
	enemy->projectiles[i].y_dir = -1;
}

static void	shoot_bot(t_entity *enemy, int i)
{
	enemy->projectiles[i].active = true;
	enemy->projectiles[i].x = enemy->x;
	enemy->projectiles[i].y = enemy->y;
	enemy->projectiles[i].x_dir = 0;
	enemy->projectiles[i].y_dir = 1;
}

static void	shoot_left(t_entity *enemy, int i)
{
	enemy->projectiles[i].active = true;
	enemy->projectiles[i].x = enemy->x;
	enemy->projectiles[i].y = enemy->y;
	enemy->projectiles[i].x_dir = -1;
	enemy->projectiles[i].y_dir = 0;
}

static void	shoot_right(t_entity *enemy, int i)
{
	enemy->projectiles[i].active = true;
	enemy->projectiles[i].x = enemy->x;
	enemy->projectiles[i].y = enemy->y;
	enemy->projectiles[i].x_dir = 1;
	enemy->projectiles[i].y_dir = 0;
}

static void	shoot_up_left(t_entity *enemy, int i)
{
	enemy->projectiles[i].active = true;
	enemy->projectiles[i].x = enemy->x;
	enemy->projectiles[i].y = enemy->y;
	enemy->projectiles[i].x_dir = - 1;
	enemy->projectiles[i].y_dir = - 1;
}

static void	shoot_up_right(t_entity *enemy, int i)
{
	enemy->projectiles[i].active = true;
	enemy->projectiles[i].x = enemy->x;
	enemy->projectiles[i].y = enemy->y;
	enemy->projectiles[i].x_dir = 1;
	enemy->projectiles[i].y_dir = -1;
}

static void	shoot_bot_left(t_entity *enemy, int i)
{
	enemy->projectiles[i].active = true;
	enemy->projectiles[i].x = enemy->x;
	enemy->projectiles[i].y = enemy->y;
	enemy->projectiles[i].x_dir = -1;
	enemy->projectiles[i].y_dir = 1;
}

static void	shoot_bot_right(t_entity *enemy, int i)
{
	enemy->projectiles[i].active = true;
	enemy->projectiles[i].x = enemy->x;
	enemy->projectiles[i].y = enemy->y;
	enemy->projectiles[i].x_dir = 1;
	enemy->projectiles[i].y_dir = 1;
}

//static bool is_enemy(unsigned char c)
//{
//    return (c == ENEMY1 || c == ENEMY2 || c == ENEMY3
//        || c == BOSS_LEFT || c == BOSS_RIGHT);
//}

static void	update_enemy1(t_entity *enemy, int frame)
{
	int		i = 0;
	bool	can_shoot = true;

	if (frame < 30 || frame > 40)
		return ;
	while (i < MAX_PROJECTILES)
		if (enemy->projectiles[i++].active)
			can_shoot = false;
	if (!can_shoot)
		return ;
	shoot_left(enemy, 0);
	shoot_right(enemy, 1);
	shoot_up(enemy, 2);
	shoot_bot(enemy, 3);
	shoot_up_left(enemy, 4);
	shoot_up_right(enemy, 5);
	shoot_bot_left(enemy, 6);
	shoot_bot_right(enemy, 7);
}

static void update_enemy2(t_entity *enemy, t_entity *hero, int frame)
{
	int         i = -1;
	int         dx, dy;
	int         dist2;
	const int   max_dist = 15;
	const int   max2 = max_dist * max_dist;

	dx = hero->x - enemy->x;
	dy = hero->y - enemy->y;
	dist2 = dx * dx + dy * dy;

	if (dist2 > ENEMY_SHOOT_RANGE || (frame % 15) != 0)
		goto skip_shoot;
	while (i < MAX_PROJECTILES - 1)
		if (!enemy->projectiles[++i].active)
			break ;
	if (hero->x - enemy->x > hero->y - enemy->y)
	{
		if (hero->y < enemy->y && hero->x > enemy->x)
			shoot_up_right(enemy, i);
		else if (hero->y < enemy->y && hero->x < enemy->x)
			shoot_up_left(enemy, i);
	}
	else if (hero->x - enemy->x < hero->y - enemy->y)
	{
		if (hero->y > enemy->y && hero->x > enemy->x)
			shoot_bot_right(enemy, i);
		else if (hero->y > enemy->y && hero->x < enemy->x)
			shoot_bot_left(enemy, i);
	}
skip_shoot:
	enemy->x_dir = 0;
	enemy->y_dir = 0;
	if ((frame % 30) != 0)
	{
		return ;
	}

	if (dist2 > max2)
	{
		if (dx > 0)
			enemy->x_dir = 1;
		else if (dx < 0)
			enemy->x_dir = -1;

		if (dy > 0)
			enemy->y_dir = 1;
		else if (dy < 0)
			enemy->y_dir = -1;

		return;
	}

	if (abs(dx) > abs(dy))
	{
		if (dx > 0)
			enemy->x_dir = 1;
		else if (dx < 0)
			enemy->x_dir = -1;
	}
	else if (abs(dy) > abs(dx))
	{
		if (dy > 0)
			enemy->y_dir = 1;
		else if (dy < 0)
			enemy->y_dir = -1;
	}
	else
	{
		int attempts = 0;

		do {
			int xdir = rand() % 3 - 1;
			int ydir = rand() % 3 - 1;

			if (!xdir && !ydir)
				continue;

			int nx = enemy->x + xdir;
			int ny = enemy->y + ydir;
			int ndx = hero->x - nx;
			int ndy = hero->y - ny;
			int nd2 = ndx * ndx + ndy * ndy;

			if (nd2 <= max2)
			{
				enemy->x_dir = xdir;
				enemy->y_dir = ydir;
				break;
			}
		} while (++attempts < 6);
	}
}

static void update_enemy3(t_entity *enemy, t_entity *hero, int frame)
{
	int         i = -1;
	int         dx, dy;
	int         dist2;
	const int   max_dist = 15;
	const int   max2 = max_dist * max_dist;

	dx = hero->x - enemy->x;
	dy = hero->y - enemy->y;
	dist2 = dx * dx + dy * dy;

	while (i < MAX_PROJECTILES - 1)
		if (!enemy->projectiles[++i].active)
			break ;

	if (sqrt(dist2) <= ENEMY_SHOOT_RANGE && frame < 6)
	{
		if (abs(dx) >= abs(dy))
		{
			if (dx > 0)
				shoot_right(enemy, i);
			else if (dx < 0)
				shoot_left(enemy, i);
		}
		else
		{
			if (dy > 0)
				shoot_bot(enemy, i);
			else if (dy < 0)
				shoot_up(enemy, i);
		}
	}

	enemy->x_dir = 0;
	enemy->y_dir = 0;

	if ((frame % 20) != 0)
		return ;

	if (dist2 > max2)
	{
		if (abs(dx) >= abs(dy))
		{
			if (dx > 0)
				enemy->x_dir = 1;
			else if (dx < 0)
				enemy->x_dir = -1;
		}
		else
		{
			if (dy > 0)
				enemy->y_dir = 1;
			else if (dy < 0)
				enemy->y_dir = -1;
		}
	}
	else
	{
		if (abs(dx) > abs(dy))
		{
			if (dx > 0)
				enemy->x_dir = 1;
			else if (dx < 0)
				enemy->x_dir = -1;
		}
		else if (abs(dy) > abs(dx))
		{
			if (dy > 0)
				enemy->y_dir = 1;
			else if (dy < 0)
				enemy->y_dir = -1;
		}
		else
		{
			int attempts = 0;

			do {
				int xdir = rand() % 3 - 1;
				int ydir = rand() % 3 - 1;

				if (!xdir && !ydir)
					continue;

				int nx = enemy->x + xdir;
				int ny = enemy->y + ydir;
				int ndx = hero->x - nx;
				int ndy = hero->y - ny;
				int nd2 = ndx * ndx + ndy * ndy;

				if (nd2 <= max2)
				{
					enemy->x_dir = xdir;
					enemy->y_dir = ydir;
					break;
				}
			} while (++attempts < 6);
		}
	}
}



static void	update_boss(t_entity *enemy, int frame)
{
	if (frame <= 30)
	{
		enemy->projectiles[0].active = true;
		enemy->projectiles[0].x = enemy->x + 3;
		enemy->projectiles[0].y = enemy->y;
		enemy->projectiles[0].x_dir = 0;
		enemy->projectiles[0].y_dir = 2;

		enemy->projectiles[1].active = true;
		enemy->projectiles[1].x = enemy->x - 2;
		enemy->projectiles[1].y = enemy->y;
		enemy->projectiles[1].x_dir = 0;
		enemy->projectiles[1].y_dir = 2;

		enemy->projectiles[2].active = true;
		enemy->projectiles[2].x = enemy->x + 3;
		enemy->projectiles[2].y = enemy->y;
		enemy->projectiles[2].x_dir = 0;
		enemy->projectiles[2].y_dir = -2;

		enemy->projectiles[3].active = true;
		enemy->projectiles[3].x = enemy->x - 2;
		enemy->projectiles[3].y = enemy->y;
		enemy->projectiles[3].x_dir = 0;
		enemy->projectiles[3].y_dir = -2;
	}
	else
	{
		enemy->projectiles[0].active = true;
		enemy->projectiles[0].x = enemy->x + 3;
		enemy->projectiles[0].y = enemy->y;
		enemy->projectiles[0].x_dir = 2;
		enemy->projectiles[0].y_dir = 2;

		enemy->projectiles[1].active = true;
		enemy->projectiles[1].x = enemy->x - 2;
		enemy->projectiles[1].y = enemy->y;
		enemy->projectiles[1].x_dir = 2;
		enemy->projectiles[1].y_dir = 2;

		enemy->projectiles[2].active = true;
		enemy->projectiles[2].x = enemy->x + 3;
		enemy->projectiles[2].y = enemy->y;
		enemy->projectiles[2].x_dir = -2;
		enemy->projectiles[2].y_dir = -2;

		enemy->projectiles[3].active = true;
		enemy->projectiles[3].x = enemy->x - 2;
		enemy->projectiles[3].y = enemy->y;
		enemy->projectiles[3].x_dir = -2;
		enemy->projectiles[3].y_dir = -2;
	}
}

extern void	update_enemy_behaviour(t_game *game, int frame)
{
	int	i = 1;

	while (i < game->ent_qty)
	{
		if (game->entities[i].alive)
		{
			if (game->entities[i].y_dir < 0)
				move_entity(game, i, UP);
			else if (game->entities[i].y_dir < 0)
				move_entity(game, i, DOWN);
			if (game->entities[i].x_dir > 0)
				move_entity(game, i, RIGHT);
			else if (game->entities[i].x_dir < 0)
				move_entity(game, i, LEFT);
			if (game->entities[i].type == BOSS_LEFT)
				update_boss(&game->entities[i], frame);
			else if (game->entities[i].type == ENEMY1)
				update_enemy1(&game->entities[i], frame);
			else if (game->entities[i].type == ENEMY2)
				update_enemy2(&game->entities[i], &game->entities[0], frame);
			else if (game->entities[i].type == ENEMY3)
				update_enemy3(&game->entities[i], &game->entities[0], frame);
		}
		i++;
	}
}
