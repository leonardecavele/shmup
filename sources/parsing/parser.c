/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:25:57 by ldecavel          #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"
#include "game.h"
#include "parser.h"
#include "entities.h"

static int	get_length(char info_line[INFO_LINE_SIZE])
{
	static int	i = 0;
	int			res = -1;

	while (isspace(info_line[i]))
		i++;
	if (isdigit(info_line[i]))
		res = atoi(&info_line[i]);
	while (isdigit(info_line[i]))
		i++;
	return (res);
}

extern int	parse(t_game *game, int fd)
{
	char	info_line[INFO_LINE_SIZE];
	int		current_line, nread;

	game->board_height = game->board_width = current_line = nread = -1;

	nread = read(fd, info_line, INFO_LINE_SIZE + 1);
	if (nread != INFO_LINE_SIZE + 1 || info_line[INFO_LINE_SIZE - 1] != '$')
		return (WRONG_INFO_LINE);
	game->board_height = get_length(info_line);	// get info
	game->board_width = get_length(info_line);	// get info


	if (game->board_height == -1 || game->board_width == -1
		|| game->board_height > 1000 - 1 || game->board_height < MIN_BOARD_HEIGHT
		|| game->board_width > 1000 - 1	|| game->board_width < MIN_BOARD_WIDTH)
		return (WRONG_SIZE_INFO);

	current_line = 0;
	while (true)
	{
		nread = read(fd, game->board[current_line], game->board_width + 1);
		if (nread != game->board_width + 1)
			break ;
		if (game->board[current_line][game->board_width] != '\n')
			return (WRONG_WIDTH_SIZE);
		current_line++;
		if (current_line == 1000)
			break ;
	}
	if (current_line != game->board_height)
		return (WRONG_HEIGHT_SIZE);

	int	j, hero_count, enemy_count, boss_count, error, i = -1;

	hero_count = enemy_count = boss_count = error = 0;
	while (++i < 1000)
	{
		j = -1;
		while (++j < 1000)
		{
			if (i < game->board_height && j < game->board_width)
			{
				if (game->board[0][j] != EMPTY || game->board[i][0] != EMPTY
					|| game->board[game->board_height - 1][j] != EMPTY
					|| game->board[i][game->board_width - 1] != EMPTY)
					error++;
				if (game->board[i][j] == HERO)
				{
					if (!hero_count)
					{
						game->entities[0].type = HERO;
						game->entities[0].x = j;
						game->entities[0].y = i;
						game->entities[0].x_dir = 0;
						game->entities[0].y_dir = -1;
					}
					hero_count++;
				}
				else if (game->board[i][j] == ENEMY1 || game->board[i][j] == ENEMY2
						|| game->board[i][j] == ENEMY3)
					enemy_count++;
				else if (game->board[i][j] == BOSS)
					boss_count++;
				else if (game->board[i][j] != WALL && game->board[i][j] != EMPTY && game->board[i][j] != GROUND)
					error++;
			}
			else
				game->board[i][j] = EMPTY;
		}
	}
	if (error || enemy_count < 1 || boss_count != 1 || hero_count != 1)
		return (WRONG_ENTITIES);
	return (0);
}
