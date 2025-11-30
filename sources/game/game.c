/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:56:10 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/30 23:07:57 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "render.h"
#include "shmup.h"

void	blink(t_game *game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		clear();
		refresh();
		napms(100);
		display_board(game);
		attron(COLOR_PAIR(2));
		mvprintw(0, 2, "HIT!");
		attroff(COLOR_PAIR(2));
		display_gui(game);
		refresh();
		napms(100);
		i++;
	}
}

static void	check_enemies_damage(t_game *game)
{
	int				hx, hy, nx, ny;
	unsigned char	tile;

	hx = game->entities[0].x;
	hy = game->entities[0].y;
	nx = hx + 1;
	ny = hy;
	if (nx < game->board_width)
	{
		tile = game->board[ny][nx];
		if (tile == ENEMY1 || tile == ENEMY2 || tile == ENEMY3
			|| tile == BOSS_LEFT || tile == BOSS_RIGHT)
			goto hit;
	}
	nx = hx - 1;
	ny = hy;
	if (nx >= 0)
	{
		tile = game->board[ny][nx];
		if (tile == ENEMY1 || tile == ENEMY2 || tile == ENEMY3
			|| tile == BOSS_LEFT || tile == BOSS_RIGHT)
			goto hit;
	}
	nx = hx;
	ny = hy + 1;
	if (ny < game->board_height)
	{
		tile = game->board[ny][nx];
		if (tile == ENEMY1 || tile == ENEMY2 || tile == ENEMY3
			|| tile == BOSS_LEFT || tile == BOSS_RIGHT)
			goto hit;
	}
	nx = hx;
	ny = hy - 1;
	if (ny >= 0)
	{
		tile = game->board[ny][nx];
		if (tile == ENEMY1 || tile == ENEMY2 || tile == ENEMY3
			|| tile == BOSS_LEFT || tile == BOSS_RIGHT)
			goto hit;
	}
	return ;
hit:
	blink(game);
	game->entities[0].hp--;
	if (game->entities[0].hp <= 0)
		game->entities[0].alive = false;
}

static void	update_passive_behaviour(t_game *game, int frame, int seconds)
{
	update_projectiles(game, frame);
	respawn_collectibles(game, seconds);
	respawn_enemy(game, seconds);
}

static int handle_user_input(int c, t_game *game, int frame)
{
	if (game->entities[0].hp && (c == 'w' || c == 's' || c == 'a' || c == 'd'))
		move_hero(c, game, frame);
	else if (game->entities[0].hp && (c == KEY_UP || c == KEY_DOWN || c == KEY_RIGHT || c == KEY_LEFT))
		hero_attack_dir(&game->entities[0], c);
	else if (game->entities[0].hp && c == ' ')
		hero_attack(&(game->entities[0]));
	else if (c == 27)
		return (1);
	return (0);
}

extern int	update_game(int c, t_game *game)
{
	static int	frame = 0;
	static int	seconds = 0;

	++frame;
	update_enemy_behaviour(game, frame);
	update_passive_behaviour(game, frame, seconds);
	if (!game->entities[0].hp)
	{
		return (HERO_DEATH);
	}
	if (handle_user_input(c, game, frame))
		return (USER_QUIT);
	if (frame == 60)
	{
		frame = 0;
		seconds++;
		if (seconds % 1 == 0)
		{
			if (game->score_calc >= 750)
			{
				while (game->score_calc >= 750)
				{
					game->score_calc -= 750;
					if (game->entities[0].hp < 5)
						game->entities[0].hp++;
				}
			}
			check_enemies_damage(game);
		}
	}
	return (0);
}
