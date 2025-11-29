/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:18:40 by abetemps          #+#    #+#             */
/*   Updated: 2025/11/29 17:18:46 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

extern void	moove_camera(int c, t_game *game)
{

	switch (c)
	{
		case ('k'):
			if (game->camera.y > 1)
				game->camera.y--;
			break;
		case ('j'):
			if (game->camera.y < game->board_height)
				game->camera.y++;
			break;
		case ('h'):
			if (game->camera.x > 1)
				game->camera.x--;
			break;
		case ('l'):
			if (game->camera.x < game->board_width)
				game->camera.x++;
			break;
	}
}
