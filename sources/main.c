/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 21:47:32 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 14:11:47 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"
#include "frame.h"
#include "game.h"
#include "render.h"
#include "parser.h"

static volatile sig_atomic_t	to_resize = true;
static volatile sig_atomic_t	fd = -1;

static void	panic(int sig)
{
	(void)sig;
	if (fd != -1)
		close(fd);
	endwin();
	exit(1);
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

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		dprintf(2, "%sPlease give a path to a map as second argument.\n", RED);
		dprintf(2, "example: ./ft_shmup map/00%s\n", RESET);
		return (2);
	}

	t_game	game = {0};
	bool	correct_size, playing = true;
	double	frame_start, frame_time, frame_end, fps;
	int		c;

	fd = open(av[1], O_RDONLY);
	if (fd < 0 || fd > FD_MAX || ((read(fd, NULL, 0) < 0)))
	{
		dprintf(2, "%sPath to map is invalid or it cannot be opened.\n", RED);
		dprintf(2, "example: ./ft_shmup map/00%s\n", RESET);
		return (3);
	}

	frame_start = frame_time = frame_end = fps = 0.0;

	parse(&game, fd);				// get map info // MUST HANDLE FAILED PARSING
	close(fd);
	fd = -1;
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
			usleep(5000);
		}
		if (correct_size == true)
		{
			c = getch();
			if (update_game(c, &game))
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
