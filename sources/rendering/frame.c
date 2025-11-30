/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 00:16:18 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/30 13:40:57 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"
#include "game.h"
#include "frame.h"

extern void	sleep_remaining(double time)
{
    struct timespec	remaining;

    if (time <= 0.0)
        return ;
    remaining.tv_sec = time;
    remaining.tv_nsec = (time - remaining.tv_sec) * 1e9;
    nanosleep(&remaining, NULL);
}

extern double	get_time(void)
{
	struct timespec tp;

	clock_gettime(CLOCK_MONOTONIC, &tp);
	return (tp.tv_sec + tp.tv_nsec / 1e9);
}

extern void	display_fps(double time, t_game *game)
{
	static int		seconds = 0;
	static int		minutes = 0;
	static int		hours = 0;

	static double	fps = 0;
	static double	added_time = 0.0;
	static int		added_frame = 0;

	added_frame++;
	added_time += time;
	mvprintw(0, 0, "%6.1f fps", fps);
	if (added_time >= 1.0)
	{
		fps = added_frame / added_time;
		added_time = 0.0;
		added_frame = 0;
		seconds++;
	}
	if (seconds == 60)
	{
		seconds = 0;
		minutes++;
	}
	if (minutes == 60)
	{
		hours++;
		minutes = 0;
	}
	mvprintw(0, 11, "%02dh%02dm%02ds", hours, minutes, seconds);
	mvprintw(0, 21, "score: %d hp: %d", game->score, game->entities[0].hp);
}
