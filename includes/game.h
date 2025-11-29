/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:57:01 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 13:59:27 by ldecavel         ###   ########lyon.fr   */
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
	unsigned short	x;
	unsigned short	y;
	unsigned short	x_dir;
	unsigned short	y_dir;
}					t_entity;

typedef struct s_camera
{
	unsigned short	x;
	unsigned short	y;
}					t_camera;

typedef struct	s_game
{
	unsigned char	board[MAX_BOARD_HEIGHT][MAX_BOARD_WIDTH];
	short			board_height;
	short			board_width;
	t_entity		entities[MAX_ENTITY];
	t_camera		camera;
}					t_game;
  
int		update_game(int c, t_game *game);

#endif
