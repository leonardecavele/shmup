/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:37:54 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 13:48:07 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "game.h"

# define FD_MAX				1024
# define INFO_LINE_SIZE		16

# define MIN_BOARD_HEIGHT	30
# define MIN_BOARD_WIDTH	30

bool	parse(t_game *game, int fd);

#endif
