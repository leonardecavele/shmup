/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:56:10 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 11:49:09 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "render.h"
#include "shmup.h"

extern int	update_game(int c, t_game *game)		// if returns not 0, game is ended
{
	// c -> user input
	// modifies entity positions (& cam ??)
	if (c == 'h' || c == 'j' || c == 'k' || c == 'l')
		move_camera(c, game);
	else if (c == 'w' || c == 's' || c == 'a' || c == 'd')
		move_hero(c, game);
	return (0);
}
