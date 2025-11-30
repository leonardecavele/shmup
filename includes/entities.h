/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 13:59:37 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/30 02:11:14 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H

# define HERO	'+'
# define PROJ	'Y'
# define ENEMY1	'B'
# define ENEMY2	'_'
# define ENEMY3	'*'
# define BOSS_LEFT	'('
# define BOSS_RIGHT	'~'
# define WALL1	'!'
# define WALL2	'"'
# define WALL3	'#'
# define WALL4	','
# define WALL5	'-'
# define WALL6	';'
# define WALL7	'<'
# define WALL8	'='
# define EMPTY	')' 
# define GROUND ' '

enum	e_mooves
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

#endif
