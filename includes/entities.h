/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 13:59:37 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 15:55:29 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H

# define HERO	'@'
# define PROJ	'*'
# define ENEMY1	'1'
# define ENEMY2	'2'
# define ENEMY3	'3'
# define BOSS	'&'
# define WALL	'#'
# define EMPTY	'.' 
# define GROUND '^'

enum	e_mooves
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

#endif
