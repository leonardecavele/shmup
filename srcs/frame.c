/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 00:16:18 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 10:30:16 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"
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

extern void	display_fps(double time) 
{
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
	}
}
