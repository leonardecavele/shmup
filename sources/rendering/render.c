/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:08:21 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 11:49:23 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "render.h"
#include "shmup.h"

extern bool	resize(void)
{
	const char	message[] = "Please get a larger window.";
	int			height, width;
	
	height = width = 0;

	endwin();
	refresh();
	clear();
	getmaxyx(stdscr, height, width);
	if (height >= MIN_HEIGHT && width >= MIN_WIDTH)
		return (true);
	mvprintw(height / 2, (width / 2) - (strlen(message) / 2), message);
	return (false);
}

extern void	render(t_game *game)
{
	(void)game;

	// draw map
	// draw character
	// draw enemies

	return ;
}
