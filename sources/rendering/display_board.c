/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:03:28 by abetemps          #+#    #+#             */
/*   Updated: 2025/11/30 03:49:16 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "ncurses.h"

static bool	is_wall(unsigned char c)
{
	if (c == WALL1 || c == WALL2 || c == WALL3 || c == WALL4
		|| c == WALL5 || c == WALL6 || c == WALL7 || c == WALL8)
		return (1);
	return (0);
}

extern void	display_board(t_game *game)
{
	int x, y;
	getmaxyx(stdscr, y, x);
	int board_x, board_y = 0;
	for (int i = 1; i < x; ++i)
	{
		for (int j = 1; j < y; ++j)
		{
			board_x = i + game->camera.x;
			board_y = j + game->camera.y;
			if (board_x >= 0 && board_x < game->board_width && 
					board_y >= 0 && board_y < game->board_height)
			{
				if (is_wall(game->board[board_y][board_x]) || game->board[board_y][board_x] == EMPTY)
				{
					attron(COLOR_PAIR(2));
					mvprintw(j, i, "%c", game->board[board_y][board_x]);
					attroff(COLOR_PAIR(2));
				}
				else if (game->board[board_y][board_x] == HERO || game->board[board_y][board_x] == HERO_PROJ)
				{
					attron(COLOR_PAIR(6));
					mvprintw(j, i, "%c", game->board[board_y][board_x]);
					attroff(COLOR_PAIR(6));
				}
				else if (game->board[board_y][board_x] == BOSS_LEFT || game->board[board_y][board_x] == BOSS_RIGHT)
				{
					attron(COLOR_PAIR(2));
					mvprintw(j, i, "%c", game->board[board_y][board_x]);
					attroff(COLOR_PAIR(2));
				}
				else
					mvprintw(j, i, "%c", game->board[board_y][board_x]);
			}
		}
	}
	(void)game;
}
