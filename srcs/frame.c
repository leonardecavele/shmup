/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 00:16:18 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 01:14:09 by ldecavel         ###   ########.fr       */
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
