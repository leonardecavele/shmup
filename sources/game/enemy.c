/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 825/11/29 22:13:58 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/30 18:35:18 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"
#include "game.h"

static bool is_enemy(unsigned char c)
{
    return (c == ENEMY1 || c == ENEMY2 || c == ENEMY3
        || c == BOSS_LEFT || c == BOSS_RIGHT);
}

static bool	is_wall(unsigned char c)
{
	if (c == WALL1 || c == WALL2 || c == WALL3 || c == WALL4
			|| c == WALL5 || c == WALL6 || c == WALL7 || c == WALL8)
		return (1);
	return (0);
}

static void    random_pos(t_game *game, t_entity *ent, unsigned short *new_x, unsigned short *new_y)
{
	int try, dy, dx, nx, ny;
	try = dy = dx = nx = ny = 0;

	*new_x = ent->x;
	*new_y = ent->y;
	while (try++ < 64)
	{
		dx = (rand() % 5) - 2;
		dy = (rand() % 5) - 2;

		if (dx == 0 && dy == 0)
				continue;
		if (dx * dx + dy * dy > 4)
				continue;

		nx = ent->x + dx;
		ny = ent->y + dy;

		if (nx < 0 || nx >= game->board_width
				|| ny < 0 || ny >= game->board_height)
				continue;
		if (is_wall(game->board[ny][nx] || game->board[ny][nx] == HERO
			|| is_enemy(game->board[ny][nx])))
				continue;

		*new_x = nx;
		*new_y = ny;
		break;
	}
}

extern void	respawn_enemy(t_game *game, int seconds)
{
	int			i = 1;
	int			e_x, e_y;

	while (i < MAX_ENTITY)
	{
		e_x = game->entities[i].x;
		e_y = game->entities[i].y;
		if (!game->entities[i].alive)
		{
			if (i == 1)
			{
				if (seconds % 60 != 0)
				{
					i++;
					continue ;
				}
				game->board[e_y][e_x - 1] = BOSS_LEFT;
				game->board[e_y][e_x] = BOSS_RIGHT;
				game->entities[i].alive = true;
				game->entities[i].hp = BOSS_HP;
			}
			else if (is_enemy(game->entities[i].type) && game->entities[i].type != BOSS_LEFT)
			{
				if (seconds % 20 != 0)
				{
					i++;
					continue ;
				}
				game->entities[i].alive = true;
				game->entities[i].hp = MOB_HP;
				random_pos(game, &game->entities[i], &game->entities[i].x, &game->entities[i].y);
				game->board[game->entities[i].y][game->entities[i].x] = game->entities[i].type;
			}
		}
		i++;
	}
}

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
	(void)enemy;
	(void)i;
//	enemy->projectiles[i].active = true;
//	enemy->projectiles[i].x = enemy->x;
//	enemy->projectiles[i].y = enemy->y;
//	enemy->projectiles[i].x_dir = 0;
//	enemy->projectiles[i].y_dir = 1;
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

	if (frame == 40)
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
	bool        skip_move = false;

	dx = hero->x - enemy->x;
	dy = hero->y - enemy->y;
	dist2 = dx * dx + dy * dy;

	while (i < MAX_PROJECTILES - 1)
		if (!enemy->projectiles[++i].active)
			break ;

	if (dist2 > ENEMY_SHOOT_RANGE * ENEMY_SHOOT_RANGE)
		skip_move = true;

	if (i < MAX_PROJECTILES && (frame == 10))
	{
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
	}

	enemy->x_dir = 0;
	enemy->y_dir = 0;

	if ((frame % 20) != 0 || skip_move)
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
			int try = 0;

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
			} while (++try < 6);
		}
	}
}

static void update_enemy3(t_entity *enemy, t_entity *hero, int frame)
{
	int         i = -1;
	int         dx, dy;
	int         dist2;
	const int   max_dist = 15;
	const int   max2 = max_dist * max_dist;
	bool		skip_move = false;

	dx = hero->x - enemy->x;
	dy = hero->y - enemy->y;
	dist2 = dx * dx + dy * dy;

	while (i < MAX_PROJECTILES - 1)
		if (!enemy->projectiles[++i].active)
			break ;

	if (sqrt(dist2) > ENEMY_SHOOT_RANGE)
		skip_move = true;
	if (frame == 50)
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

	if ((frame % 20) != 0 || skip_move)
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
			int try = 0;

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
			} while (++try < 6);
		}
	}
}

void    update_boss(t_entity *enemy, t_entity *hero, int frame)
{
	static int  step = 0;
	static int  pattern = 0;
	int         any_active = 0;
	int         dx;
	int         dy;

	(void)frame;
	dx = hero->x - enemy->x;
	dy = hero->y - enemy->y;

	for (int i = 0; i < MAX_PROJECTILES; ++i)
	{
		if (enemy->projectiles[i].active)
		{
			any_active = 1;
			break;
		}
	}
	if (any_active)
		return;

	int slots[8];
	int nslots = 0;
	for (int i = 0; i < MAX_PROJECTILES && nslots < 8; ++i)
		slots[nslots++] = i;
	if (nslots == 0)
		return;

	if (pattern == 0)
	{
		static const int dirs[8][2] = {
			{ 0,  1},
			{-1,  1},
			{-1,  0},
			{-1, -1},
			{ 0, -1},
			{ 1, -1},
			{ 1,  0},
			{ 1,  1}
		};
		for (int k = 0; k < nslots; ++k)
		{
			int idx = (step + k) & 7;
			t_projectile *p = &enemy->projectiles[slots[k]];

			p->active = true;
			p->x = enemy->x + dirs[idx][0];
			p->y = enemy->y + dirs[idx][1];
			p->x_dir = dirs[idx][0];
			p->y_dir = dirs[idx][1];
		}
		step = (step + 1) & 7;
		pattern = 1;
	}
	else
	{
		int offsets[6] = { -3, -2, -1, 1, 2, 3 };
		int to_spawn = (nslots < 6) ? nslots : 6;

		if (dx * dx >= dy * dy)
		{
			int dir_x = (dx >= 0) ? 1 : -1;

			for (int k = 0; k < to_spawn; ++k)
			{
				t_projectile *p = &enemy->projectiles[slots[k]];

				p->active = true;
				p->x = enemy->x;
				p->y = enemy->y + offsets[k];
				p->x_dir = dir_x;
				p->y_dir = 0;
			}
		}
		else
		{
			int dir_y = (dy >= 0) ? 1 : -1;

			for (int k = 0; k < to_spawn; ++k)
			{
				t_projectile *p = &enemy->projectiles[slots[k]];

				p->active = true;
				p->x = enemy->x + offsets[k];
				p->y = enemy->y;
				p->x_dir = 0;
				p->y_dir = dir_y;
			}
		}
		pattern = 0;
	}
}

extern void	update_enemy_behaviour(t_game *game, int frame)
{
	int	i = 1;

	while (i < game->ent_qty)
	{
		if (game->entities[i].alive)
		{
			if (game->entities[i].type == BOSS_LEFT)
				update_boss(&game->entities[1], &game->entities[0], frame);
			else if (game->entities[i].type == ENEMY1)
				update_enemy1(&game->entities[i], frame);
			else if (game->entities[i].type == ENEMY2)
				update_enemy2(&game->entities[i], &game->entities[0], frame);
			else if (game->entities[i].type == ENEMY3)
				update_enemy3(&game->entities[i], &game->entities[0], frame);
		}
		if (game->entities[i].y_dir < 0 || !game->entities[i].alive)
			move_entity(game, i, UP);
		else if (game->entities[i].y_dir > 0 || !game->entities[i].alive)
			move_entity(game, i, DOWN);
		if (game->entities[i].x_dir > 0 || !game->entities[i].alive)
			move_entity(game, i, RIGHT);
		else if (game->entities[i].x_dir < 0 || !game->entities[i].alive)
			move_entity(game, i, LEFT);
		i++;
	}
}
