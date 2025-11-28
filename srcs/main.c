/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 21:47:32 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 00:19:18 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame.h"
#include <stdbool.h>

int	main(void)
{
	bool	playing = true;
	float	frame_start, frame_time, frame_end;

	while (playing)
	{
		frame_start = get_time();
		//
		// get_input();
		// update_game();
		// render();
		//
		frame_end = get_time();
		frame_time = frame_end - frame_start;
		if (frame_time < TARGET_FRAME_TIME)
			sleep_remaining(TARGET_FRAME_TIME - frame_time);
	}
	return (0);
}
