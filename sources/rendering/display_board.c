/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:03:28 by abetemps          #+#    #+#             */
/*   Updated: 2025/11/29 16:28:09 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "ncurses.h"


extern void	display_board(t_game *game)
{
	int x, y;
	getmaxyx(stdscr, y, x);
	for (int i = 1; i < x; ++i)
	{
		for (int j = 1; j < y; ++j)
		{
			int board_x = i + game->camera.x;
			int board_y = j + game->camera.y;
			if (board_x >= 0 && board_x < game->board_width && 
					board_y >= 0 && board_y < game->board_height)
			{
				mvprintw(j, i, "%c", game->board[board_y][board_x]);
			}
			else
			{
				mvprintw(j, i, "X"); 
			}			
		}
	}
	(void)game;
}
