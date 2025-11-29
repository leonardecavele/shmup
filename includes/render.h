/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 09:17:26 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 16:08:10 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <stdbool.h>
# include "text_formatting.h"

# define MIN_WIDTH	80
# define MIN_HEIGHT	30
# define TILE_SIZE	2

bool	resize(void);
void	render(t_game *game);

void	moove_camera(int c, t_game *game);
void	display_board(t_game *game);

#endif
