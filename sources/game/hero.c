/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hero.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:30:39 by abetemps          #+#    #+#             */
/*   Updated: 2025/11/29 19:25:45 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "render.h"
#include "ncurses.h"

extern void	move_hero(int c, t_game *game)
{
	int max_y, max_x;
	int screen_x, screen_y;
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
