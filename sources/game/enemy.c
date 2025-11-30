/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 22:13:58 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/30 03:42:58 by abetemps         ###   ########.fr       */
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

static void	update_enemy1(t_entity *enemy, int frame)
{
	int		i = 0;
	bool	can_shoot = true;

	if (frame < 15)
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

static void	update_enemy2(t_entity *enemy, t_entity *hero, int frame)
{
	int		i = -1;
	int		distance, dx, dy;

	dx = dy = 0;
	dx = hero->x - enemy->x;
	dy = hero->y - enemy->y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance > ENEMY_SHOOT_RANGE || (frame >= 15 && frame <= 30) || (frame >= 45 && frame <= 60))
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
	do {
        enemy->x_dir = rand() % 3 - 1;
        enemy->y_dir = rand() % 3 - 1;
    } while (!enemy->x_dir && !enemy->y_dir);
}

static void	update_enemy3(t_entity *enemy, t_entity *hero, int frame)
{
	int		i = -1;
	int		dx, dy, distance;

	dx = dy = 0;
	while (i < MAX_PROJECTILES - 1)
		if (!enemy->projectiles[++i].active)
			break ;
	dx = hero->x - enemy->x;
	dy = hero->y - enemy->y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance > ENEMY_SHOOT_RANGE)
		goto skip_shoot;
	if (abs(hero->x - enemy->x) > abs(hero->y - enemy->y))
	{
		if (hero->x - enemy->x > 0)
			shoot_right(enemy, i);
		else
			shoot_left(enemy, i);
	}
	else
	{
		if (hero->y - enemy->y > 0)
			shoot_bot(enemy, i);
		else
			shoot_up(enemy, i);
	}
skip_shoot:
	if ((frame >= 5 && frame <= 25) || (frame >= 35 && frame <= 45))
	do {
        enemy->x_dir = rand() % 3 - 1;
        enemy->y_dir = rand() % 3 - 1;
    } while (!enemy->x_dir && !enemy->y_dir);
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
