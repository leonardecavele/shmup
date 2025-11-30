/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:56:10 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/30 15:42:00 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "render.h"
#include "shmup.h"

static void	update_passive_behaviour(t_game *game, int frame, int seconds)
{
	update_projectiles(game, frame);
	respawn_enemy(game, seconds);
}

static int handle_user_input(int c, t_game *game, int frame)
{
	if (c == 'h' || c == 'j' || c == 'k' || c == 'l')
		move_camera(c, game);
	else if (c == 'w' || c == 's' || c == 'a' || c == 'd')
		move_hero(c, game, frame);
	else if (c == KEY_UP || c == KEY_DOWN || c == KEY_RIGHT || c == KEY_LEFT)
		hero_attack_dir(&game->entities[0], c);
	else if (c == ' ')
		hero_attack(&(game->entities[0]));
	else if (c == 'q')
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
	}
	return (0);
}
