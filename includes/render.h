/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 09:17:26 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/30 00:29:27 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <stdbool.h>
# include "text_formatting.h"

# define MIN_WIDTH	80
# define MIN_HEIGHT	32
# define MAX_WIDTH	90
# define MAX_HEIGHT 42


bool	resize(void);
void	render(t_game *game);

void	move_camera(int c, t_game *game);
void	display_board(t_game *game);

#endif
