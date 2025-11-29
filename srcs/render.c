/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:08:21 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 10:51:03 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "shmup.h"

// to simulate layers we can draw in a specific order

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

void	render(void)
{
	// draw map
	// draw character
	// draw enemies
	// refresh();
}
