/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:57:01 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 11:51:56 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# define MAX_ENTITY			30
# define MAX_BOARD_WIDTH	1000
# define MAX_BOARD_HEIGHT	1000

typedef struct	s_entity
{
	unsigned char	entity;
	short			x;
	short			y;
	short			x_dir;
	short			y_dir;
}					t_entity;

typedef struct	s_game
{
	unsigned char	board[MAX_BOARD_HEIGHT][MAX_BOARD_WIDTH];
	t_entity		entities[MAX_ENTITY];
}					t_game;
  
int	update_game(int c, t_game *game);

#endif
