/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 09:17:26 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/30 16:33:07 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <stdbool.h>
# include "game.h"
# include "text_formatting.h"

# define MIN_WIDTH	40
# define MIN_HEIGHT	22
# define MAX_WIDTH	100
# define MAX_HEIGHT 142


bool	resize(void);
void	render(t_game *game);

void	move_camera(int c, t_game *game);
void	display_board(t_game *game);
void	display_gui(t_game *game);

#endif
