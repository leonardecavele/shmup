/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:03:55 by abetemps          #+#    #+#             */
/*   Updated: 2025/11/30 00:43:31 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <ncurses.h>

static int	update_projectile(t_game *game, t_projectile *proj, unsigned short *active_proj)
{
	mvprintw(0, 110, "%dx %dy", proj->x, proj->y);
	// hit system
	if (game->board[proj->x + proj->x_dir][proj->y + proj->y_dir] == HERO)
	{
		game->entities[0].alive = false;
		proj->active = false;
		--(*active_proj);
		mvprintw(0, 100, "HEROHIT");
		return (1);
	}
	else if (game->board[proj->x + proj->x_dir][proj->y + proj->y_dir] == WALL)
	{
		mvprintw(0, 100, "WALLHIT");
		proj->active = false;
		game->board[proj->x][proj->y] = GROUND;
		--(*active_proj);
		return (2);
	}
	mvprintw(0, 100, "MOVE");
	if (game->board[proj->x][proj->y] != HERO)
		game->board[proj->x][proj->y] = GROUND;
	proj->x += proj->x_dir;
	proj->y += proj->y_dir;
	game->board[proj->x][proj->y] = PROJ;
	
	return (0);
}

extern void	update_projectiles(t_game *game, int frame)
{
	int hit = 0;

	if (frame % 2)
		return;
	int i = 0;
	// for (int i = 0; i < game->ent_qty; ++i)
	// {
		for (int j = 0; j < MAX_PROJECTILES; ++j)
		{
			if (game->entities[i].projectiles[j].active)
			{
				mvprintw(0, 70, "%d is checked", j);
				hit = update_projectile(game, &(game->entities[i].projectiles[j]), &(game->entities[i].active_proj_qty));
			}
		}
	// }
}
