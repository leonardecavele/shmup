/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 00:17:01 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 01:43:23 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAME_H
# define FRAME_H

# include <time.h>

# define TARGET_FRAME_TIME 1.0 / 60.0

void	sleep_remaining(double time);
double	get_time(void);
void	display_fps(double time);

#endif
