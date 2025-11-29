/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:25:57 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 13:58:14 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"
#include "game.h"
#include "parser.h"

static int	get_length(char info_line[INFO_LINE_SIZE])
{
	static int	i = 0;
	int			res = -1;

	while (isspace(info_line[i]))
		i++;
	if (isdigit(info_line[i]))
		res = atoi(info_line[i]);
	while (isdigit(info_line[i]))
		i++;
	return (res);
}

extern bool	parse(t_game *game, int fd)
{
	char	info_line[INFO_LINE_SIZE];
	int		game->board_height, game->board_width, current_line, nread, i = 0;

	game->board_height = game->board_width = current_line = nread = -1;

	nread = read(fd, info_line, INFO_LINE_SIZE);
	if (nread != INFO_LINE_SIZE || info_line[INFO_LINE_SIZE - 1] != '$')	// line terminated
		return (false);
	game->board_height = get_length(info_line);	// get info
	game->board_width = get_length(info_line);	// get info

	if (game->board_height == -1 || game->board_width == -1
		|| game->board_height > 1000 - 2 || game->board_height < MIN_BOARD_HEIGHT
		|| game->board_width > 1000 - 2	|| game->board_width < MIN_BOARD_WIDTH)
		return (false);														// invalid infos

	current_line = 1000 - game->board_height;
	while (true)
	{
		nread = read(fd, game->board[current_line], game->board_width);
		if (nread != game->board_width)
			break ;
		if (game->board[current_line][game->board_width] != '\n')
			return (false);
		current_line++;
		if (current_line == 1000)
			break ;
	}
	if (current_line == 1000
		&& 1000 - game->board_height != current_line - game->board_height)
		return (false);
	return (true);
}
