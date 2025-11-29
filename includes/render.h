/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 09:17:26 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 21:37:12 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <stdbool.h>

# define MIN_WIDTH	80
# define MIN_HEIGHT	32
# define MAX_WIDTH	100
# define MAX_HEIGHT 52

#define RESET	"\033[0m"
#define RED		"\033[31m"

bool	resize(void);

#endif
