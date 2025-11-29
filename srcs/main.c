/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 21:47:32 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 01:45:57 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"
#include "frame.h"

int	main(void)
{
	bool	playing = true;
	double	frame_start, frame_time, frame_end, fps;

	frame_start = frame_time = frame_end = fps = 0.0;

	initscr();					// init screen
	cbreak();					// keys instantly works
	noecho();					// typed char are not printed
	nodelay(stdscr, true);		// getch returns ERR if no char
	curs_set(0);				// hide cursor

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

		display_fps(get_time() - frame_start);
	}
	endwin();					// end screen
	return (0);
}
