/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:57:01 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/30 00:39:44 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "shmup.h"
# include "entities.h"

# define MAX_ENTITY			30
# define MAX_PROJECTILES	10
# define MAX_BOARD_WIDTH	1000
# define MAX_BOARD_HEIGHT	1000
# define CAM_TRESH			8
# define ENEMY_SHOOT_RANGE	10

typedef	struct		s_projectile
{
	unsigned short	x;
	unsigned short	y;
	unsigned short	x_dir;
	unsigned short	y_dir;
	bool			active;
}					t_projectile;

typedef struct		s_entity
{
	unsigned char	type;
	unsigned short	x;
	unsigned short	y;
	unsigned short	x_dir;
	unsigned short	y_dir;
	t_projectile	projectiles[MAX_PROJECTILES];
	bool			alive;
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
	int				score;
	int				hp;
	t_entity		entities[MAX_ENTITY];
	unsigned short	ent_qty;
	t_camera		camera;
}					t_game;
  
int		update_game(int c, t_game *game);
void	move_hero(int c, t_game *game, int frame);
void	hero_attack(t_game *game);
void	update_enemy_behaviour(t_game *game, int frame);
void	move_entity(t_game *game, short which, short move);

#endif
