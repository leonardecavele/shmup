/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 22:13:58 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/30 00:14:43 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"
#include "game.h"

static void	shoot_up(t_entity *enemy, int i)
{
	enemy->projectiles[i].active = true;
	enemy->projectiles[i].x = enemy->x;
	enemy->projectiles[i].y = enemy->y - 1;
	enemy->projectiles[i].x_dir = 0;
	enemy->projectiles[i].y_dir = -1;
}

static void	shoot_bot(t_entity *enemy, int i)
{
	enemy->projectiles[i].active = true;
	enemy->projectiles[i].x = enemy->x;
	enemy->projectiles[i].y = enemy->y + 1;
	enemy->projectiles[i].x_dir = 0;
	enemy->projectiles[i].y_dir = 1;
}

static void	shoot_left(t_entity *enemy, int i)
{
	enemy->projectiles[i].active = true;
	enemy->projectiles[i].x = enemy->x - 1;
	enemy->projectiles[i].y = enemy->y;
	enemy->projectiles[i].x_dir = -1;
	enemy->projectiles[i].y_dir = 0;
}

static void	shoot_right(t_entity *enemy, int i)
{
	enemy->projectiles[i].active = true;
	enemy->projectiles[i].x = enemy->x + 1;
	enemy->projectiles[i].y = enemy->y;
	enemy->projectiles[i].x_dir = 1;
	enemy->projectiles[i].y_dir = 0;
}

static void	shoot_up_left(t_entity *enemy, int i)
{
	enemy->projectiles[i].active = true;
	enemy->projectiles[i].x = enemy->x - 1;
	enemy->projectiles[i].y = enemy->y - 1;
	enemy->projectiles[i].x_dir = - 1;
	enemy->projectiles[i].y_dir = - 1;
}

static void	shoot_up_right(t_entity *enemy, int i)
{
	enemy->projectiles[i].active = true;
	enemy->projectiles[i].x = enemy->x + 1;
	enemy->projectiles[i].y = enemy->y - 1;
	enemy->projectiles[i].x_dir = 1;
	enemy->projectiles[i].y_dir = -1;
}

static void	shoot_bot_left(t_entity *enemy, int i)
{
	enemy->projectiles[i].active = true;
	enemy->projectiles[i].x = enemy->x - 1;
	enemy->projectiles[i].y = enemy->y + 1;
	enemy->projectiles[i].x_dir = -1;
	enemy->projectiles[i].y_dir = 1;
}

static void	shoot_bot_right(t_entity *enemy, int i)
{
	enemy->projectiles[i].active = true;
	enemy->projectiles[i].x = enemy->x + 1;
	enemy->projectiles[i].y = enemy->y + 1;
	enemy->projectiles[i].x_dir = 1;
	enemy->projectiles[i].y_dir = 1;
}

static void	update_enemy1(t_entity *enemy, int frame)
{
	int		i = 0;
	bool	can_shoot = true;

	if (frame < 15 || (frame >= 30 && frame <= 45))
		return ;
	while (i < MAX_PROJECTILES)
		if (enemy->projectiles[i++].active)
			can_shoot = false;
	if (!can_shoot)
		return ;
	shoot_left(enemy, 1);
	shoot_right(enemy, 2);
	shoot_up(enemy, 3);
	shoot_bot(enemy, 4);
	shoot_up_left(enemy, 5);
	shoot_up_right(enemy, 6);
	shoot_bot_left(enemy, 7);
	shoot_bot_right(enemy, 8);
}

static void	update_enemy2(t_entity *enemy, t_entity *hero, int frame)
{
	int		i = -1;
	int		distance, dx, dy;

	dx = dy = 0;
	if ((frame >= 15 && frame <= 30) && (frame >= 45 && frame <= 60))
		goto skip_shoot;
	while (i < MAX_PROJECTILES)
		if (!enemy->projectiles[++i].active)
			break ;
	dx = hero->x - enemy->x;
	dy = hero->y - enemy->y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance > ENEMY_SHOOT_RANGE)
		return ;
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
    } while (!dx && !dy);
}

static void	update_enemy3(t_entity *enemy, t_entity *hero, int frame)
{
	int		i = -1;
	int		distance, dx, dy;

	while (i < MAX_PROJECTILES)
		if (!enemy->projectiles[++i].active)
			break ;
	dx = hero->x - enemy->x;
	dy = hero->y - enemy->y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance > ENEMY_SHOOT_RANGE)
		return ;
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
	if ((frame >= 5 && frame <= 25) && (frame >= 35 && frame <= 45))
	do {
        enemy->x_dir = rand() % 3 - 1;
        enemy->y_dir = rand() % 3 - 1;
    } while (!dx && !dy);
}

extern void	update_enemy_behaviour(t_game *game, int frame)
{
	int	i = 2;

	while (i < game->ent_qty)
	{
		if (game->entities[i].alive)
		{
			if (game->entities[i].type == ENEMY1)
				update_enemy1(&game->entities[i], frame);
			else if (game->entities[i].type == ENEMY2)
				update_enemy2(&game->entities[i], &game->entities[0], frame);
			else if (game->entities[i].type == ENEMY3)
				update_enemy3(&game->entities[i], &game->entities[0], frame);
		}
		i++;
	}
}
