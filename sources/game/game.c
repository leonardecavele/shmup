/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:56:10 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 23:49:39 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "render.h"
#include "shmup.h"

static void	update_passive_behaviour(t_game *game)
{
	(void)game;
	// animate sprites
	// move_projectiles
}

static int handle_user_input(int c, t_game *game)
{
	if (c == 'h' || c == 'j' || c == 'k' || c == 'l')
		move_camera(c, game);
	else if (c == 'w' || c == 's' || c == 'a' || c == 'd')
		move_hero(c, game);
	else if (c == ' ')
		hero_attack(game);
	else if (c == 'q')
		return (1);
	return (0);
}
extern int	update_game(int c, t_game *game)
{
	static int	frame = 0;

	frame++;
	update_enemy_behaviour(game, frame);
	update_passive_behaviour(game);
	if (handle_user_input(c, game, frame))
		return (1);
	if (frame == 60)
		frame = 0;
	return (0);
}
