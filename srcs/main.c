/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 21:47:32 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 10:51:18 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"
#include "frame.h"
#include "game.h"
#include "render.h"

static volatile sig_atomic_t	to_resize = true;

static void	panic(int sig)
{
	(void)sig;
	endwin();
	exit(0);
}

static void	handle_winch(int sig)
{
	(void)sig;
	to_resize = true;
}

static void	handle_signal(void)
{
	signal(SIGINT, panic);
	signal(SIGTERM, panic);
	signal(SIGQUIT, panic);
	signal(SIGWINCH, handle_winch);
}

int	main(void)
{
	bool	correct_size, playing = true;
	double	frame_start, frame_time, frame_end, fps;
	int		c;

	frame_start = frame_time = frame_end = fps = 0.0;

	handle_signal();				// to properly exit
	initscr();						// init screen
	cbreak();						// keys instantly works
	noecho();						// typed char are not printed
	nodelay(stdscr, true);			// getch returns ERR if no char
	curs_set(0);					// hide cursor

	while (playing)
	{
		frame_start = get_time();

		if (to_resize)
		{
			correct_size = resize();
			if (correct_size)
				to_resize = false;
		}
		if (correct_size == true)
		{
			c = getch();
			if (update_game(c))
				playing = false;

			clear();
			mvprintw(5, 10, "running");
			// render();
		}

		frame_end = get_time();
		frame_time = frame_end - frame_start;
		if (frame_time < TARGET_FRAME_TIME)
			sleep_remaining(TARGET_FRAME_TIME - frame_time);
		display_fps(get_time() - frame_start);
		refresh();
	}
	endwin();
	return (0);
}
