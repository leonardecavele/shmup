/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hero.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:30:39 by abetemps          #+#    #+#             */
/*   Updated: 2025/11/29 18:38:11 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

extern void	move_hero(int c, t_game *game)
{
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
}
