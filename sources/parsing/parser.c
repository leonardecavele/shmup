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
#include "render.h"
#include "entities.h"

static bool	is_wall(unsigned char c)
{
	if (c == WALL1 || c == WALL2 || c == WALL3 || c == WALL4
		|| c == WALL5 || c == WALL6 || c == WALL7 || c == WALL8)
		return (1);
	return (0);
}

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
	char	info_line[INFO_LINE_SIZE + 1];
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
						game->entities[0].hp = HERO_HP;
						game->entities[0].x = j;
						game->entities[0].y = i;
						game->entities[0].x_dir = 0;
						game->entities[0].y_dir = 0;
						game->entities[0].dir = UP;
					}
					++hero_count;
				}
				else if (game->board[i][j] == COLLEC)
				{
					game->collectibles[game->collec_qty].x = j; 
					game->collectibles[game->collec_qty].y = i;
					game->collectibles[game->collec_qty].active = true 
					game->collec_qty++;
				}
				else if (game->board[i][j] == ENEMY1 || game->board[i][j] == ENEMY2
						|| game->board[i][j] == ENEMY3)
				{
					game->entities[game->ent_qty].type = game->board[i][j];
					game->entities[game->ent_qty].x = j;
					game->entities[game->ent_qty].y = i;
					game->entities[game->ent_qty].hp = MOB_HP;
					game->entities[game->ent_qty].alive = true;
					game->ent_qty++;
					enemy_count++;
				}
				else if (game->board[i][j] == BOSS_LEFT)
				{
					j++;
					if (game->board[i][j] != BOSS_RIGHT)
						return (WRONG_ENTITIES);
					game->entities[1].type = BOSS_LEFT;
					game->entities[1].hp = BOSS_HP;
					game->entities[1].x = j;
					game->entities[1].y = i;
					game->entities[1].alive = true;
					boss_count++;
				}
				else if (!is_wall(game->board[i][j]) && game->board[i][j] != EMPTY && game->board[i][j] != GROUND)
					error++;
			}
			else
				game->board[i][j] = EMPTY;
		}
	}
	if (error || enemy_count < 1 || boss_count != 1 || hero_count != 1)
		return (WRONG_ENTITIES);
	game->camera.x = (game->entities[0].x + 0.5f) - MIN_WIDTH;
	game->camera.y = (game->entities[0].y + 0.5f) - MIN_HEIGHT;
	return (0);
}
