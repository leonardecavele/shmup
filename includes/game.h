/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:57:01 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/30 15:55:42 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdbool.h>
# include "shmup.h"
# include "entities.h"

# define MAX_ENTITY			30
# define MAX_PROJECTILES	8
# define MAX_BOARD_WIDTH	1000
# define MAX_BOARD_HEIGHT	1000
# define CAM_TRESH			8
# define ENEMY_SHOOT_RANGE	20
# define MOB_HP				1
# define BOSS_HP			5
# define HERO_HP			3
# define HERO_MAX_HP		5

enum				e_quit
{
	USER_QUIT = 1,
	HERO_DEATH,
};

enum				e_hit
{
	OUTOFBOUND,
	NO_HIT,
	WALL_HIT,
	HERO_HIT,
	ENEMY_HIT,
	BOSS_HIT,
	TIME_NO_SHOOT
};

enum				e_collectible
{
	HEAL,
	POINT,
};

typedef	struct		s_projectile
{
	unsigned short	x;
	unsigned short	y;
	short			x_dir;
	short			y_dir;
	bool			active;
}					t_projectile;

typedef	struct		s_collectible
{
	unsigned short	type;
	unsigned short	x;	
	unsigned short	y;	
	bool			active;
}					t_collectible;

typedef struct		s_entity
{
	unsigned char	type;
	unsigned short	x;
	unsigned short	y;
	short			hp;
	short			x_dir;
	short			y_dir;
	short			dir;
	t_projectile	projectiles[MAX_PROJECTILES];
	unsigned short	active_proj_qty;
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
	t_entity		entities[MAX_ENTITY];
	unsigned short	ent_qty;
	t_camera		camera;
}					t_game;
  
int			update_game(int c, t_game *game);
void		move_hero(int c, t_game *game, int frame);
void		hero_attack(t_entity *hero);
void		hero_attack_dir(t_entity *hero, int c);
void		update_enemy_behaviour(t_game *game, int frame);
void		move_entity(t_game *game, short which, short move);
void		update_projectiles(t_game *game, int frame);
void		respawn_enemy(t_game *game, int seconds);
t_entity	*find_entity(t_entity *entities, short x, short y);

#endif
