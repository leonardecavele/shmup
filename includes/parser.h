/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:37:54 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 18:26:50 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "game.h"

# define FD_MAX					1024
# define INFO_LINE_SIZE			16

# define MIN_BOARD_HEIGHT		42
# define MIN_BOARD_WIDTH		100

# define WRONG_INFO_LINE		1
# define WRONG_SIZE_INFO		2
# define WRONG_WIDTH_SIZE		3
# define WRONG_HEIGHT_SIZE		4
# define WRONG_ENTITIES			5

int	parse(t_game *game, int fd);

#endif
