/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:56:10 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/30 00:10:09 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "render.h"
#include "shmup.h"

static void	update_passive_behaviour(t_game *game, int frame)
{
	// animate sprites
	update_projectiles(game);
}

static int handle_user_input(int c, t_game *game, int frame)
{
	if (c == 'h' || c == 'j' || c == 'k' || c == 'l')
		move_camera(c, game);
	else if (c == 'w' || c == 's' || c == 'a' || c == 'd')
		move_hero(c, game);
	else if (c == KEY_UP || c == KEY_DOWN || c == KEY_RIGHT || c == KEY_LEFT)
		hero_attack_dir(game->entities[0].projectiles, c);
	else if (c == ' ')
		hero_attack(&(game->entities[0]));
	else if (c == 'q')
		return (1);
	return (0);
}
extern int	update_game(int c, t_game *game)
{
	static int	frame = 0;

	frame++;
	update_enemy_behaviour(game, frame);
	update_passive_behaviour(game, frame);
	if (handle_user_input(c, game, frame))
		return (1);
	if (frame == 60)
		frame = 0;
	return (0);
}
