/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hero.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:30:39 by abetemps          #+#    #+#             */
/*   Updated: 2025/11/30 03:00:16 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "render.h"
#include "ncurses.h"

extern void	move_hero(int c, t_game *game, int frame)
{
	int max_y, max_x;
	int screen_x, screen_y;
	
	(void)frame;
	getmaxyx(stdscr, max_y, max_x);
	switch (c)
	{
		case ('w'):
			move_entity(game, 0, UP);
			break;
		case ('s'):
			move_entity(game, 0, DOWN);
			break;
		case ('a'):
			move_entity(game, 0, LEFT);
			break;
		case ('d'):
			move_entity(game, 0, RIGHT);
			break;
	}
	screen_x = game->entities[0].x - game->camera.x;
	screen_y = game->entities[0].y - game->camera.y;
	if (screen_y <= CAM_TRESH && game->camera.y > 0)
		--game->camera.y;
	else if (screen_y >= max_y - CAM_TRESH && game->camera.y < game->board_height - max_y)
		++game->camera.y;
	if (screen_x <= CAM_TRESH && game->camera.x > 0)
		--game->camera.x;
	else if (screen_x >= max_x - CAM_TRESH && game->camera.x < game->board_width - max_x)
		++game->camera.x;
}

extern void	hero_attack_dir(t_entity *hero, int c)
{
	for (int i = 0; i < MAX_PROJECTILES; ++i)
	{
		switch (c)
		{
			case (KEY_UP):
				mvprintw(0, 40, "U");
				hero->dir = UP;
				break;
			case (KEY_DOWN):
				mvprintw(0, 40, "D");
				hero->dir = DOWN;
				break;
			case (KEY_LEFT):
				mvprintw(0, 40, "L");
				hero->dir = LEFT;
				break;
			case (KEY_RIGHT):
				mvprintw(0, 40, "R");
				hero->dir = RIGHT;
				break;
		}
	}
}

extern void	hero_attack(t_entity *hero)
{
	int					i = 0;

	for (int j = 0; j < MAX_PROJECTILES; ++j)
	{
		mvprintw(0, 40 + j + 1, (hero->projectiles[j].active ? "x" : "o"));
	}
	if (hero->active_proj_qty == MAX_PROJECTILES)
	{
		return;
	}
	while (i < MAX_PROJECTILES && hero->projectiles[i].active)
		++i;
	switch (hero->dir)
	{
		case (UP):
			hero->projectiles[i].x_dir = 0;
			hero->projectiles[i].y_dir = -1;
			break;
		case (DOWN):
			hero->projectiles[i].x_dir = 0;
			hero->projectiles[i].y_dir = 1;
			break;
		case (LEFT):
			hero->projectiles[i].x_dir = -1;
			hero->projectiles[i].y_dir = 0;
			break;
		case (RIGHT):
			hero->projectiles[i].x_dir = 1;
			hero->projectiles[i].y_dir = 0;
			break;
	}
	hero->projectiles[i].x = hero->x;
	hero->projectiles[i].y = hero->y;
	hero->projectiles[i].active = true;
	++hero->active_proj_qty;
}
