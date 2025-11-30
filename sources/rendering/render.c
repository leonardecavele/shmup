/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:08:21 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/30 00:31:08 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "render.h"
#include "shmup.h"

extern bool	resize(void)
{
	const char	message[] = "Please get a window larger than 100x42.";
	int			height, width;
	
	height = width = 0;

	endwin();
	refresh();
	clear();
	getmaxyx(stdscr, height, width);
	if (height == HEIGHT && width == WIDTH)
		return (true);
	mvprintw(height  >> 1, (width  >> 1) - (strlen(message)  >> 1), message);
	return (false);
}

extern void	render(t_game *game)
{
	display_gui(game);
	display_board(game);
	return ;
}
