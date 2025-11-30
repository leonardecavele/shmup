/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 21:47:32 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/30 13:43:20 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"
#include "frame.h"
#include "game.h"
#include "render.h"
#include "parser.h"
#include "text_formatting.h"

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
		dprintf(2, "example: ./ft_shmup map/00%s\n", RST);
		return (2);
	}

	t_game	game = {0};
	bool	correct_size, playing = true;
	double	frame_start, frame_time, frame_end, fps;
	int		c, ret;

	fd = open(av[1], O_RDONLY);
	if (fd < 0 || fd > FD_MAX || ((read(fd, NULL, 0) < 0)))
	{
		dprintf(2, "%sPath to map is invalid or it cannot be opened.\n", RED);
		dprintf(2, "example: ./ft_shmup map/00%s\n", RST);
		return (3);
	}

	frame_start = frame_time = frame_end = fps = 0.0;

	game.ent_qty = 2;
	if ((ret = parse(&game, fd)))			// get map info // MUST HANDLE FAILED PARSING
	{
		dprintf(2, "%sMap is invalid.\n", RED);
		if (ret == WRONG_INFO_LINE)
			dprintf(2, "Info line is incorrect.\n%s", RST);
		else if (ret == WRONG_SIZE_INFO)
			dprintf(2, "Info line sizes are incorrect.\n%s", RST);
		else if (ret == WRONG_WIDTH_SIZE)
			dprintf(2, "Width doesnt match the info line.\n%s", RST);
		else if (ret == WRONG_HEIGHT_SIZE)
			dprintf(2, "Height doesnt match the info line.\n%s", RST);
		else if (ret == WRONG_ENTITIES)
			dprintf(2, "Entities are incorrect.\n%s", RST);
		return (4);
	}
	close(fd);
	fd = -1;
	srand(time(NULL));
	handle_signal();				// to properly exit
	initscr();						// init screen
	cbreak();						// keys instantly works
	noecho();						// typed char are not printed
	nodelay(stdscr, true);			// getch returns ERR if no char
	keypad(stdscr, TRUE);
	curs_set(0);					// hide cursor
									//

	game.score = 0;
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
			int quit = update_game(c, &game);
			switch (quit)
			{
				case (0):
					break;
				case (USER_QUIT):
					// menu fin
					playing = false;
					break;
				case (HERO_DEATH):
					// menu death
					playing = false;
					break;
			}
			render(&game);
		}
		frame_end = get_time();
		frame_time = frame_end - frame_start;
		if (frame_time < TARGET_FRAME_TIME)
			sleep_remaining(TARGET_FRAME_TIME - frame_time);
		display_fps(get_time() - frame_start, &game);
		refresh();
	}
	endwin();
	return (0);
}
