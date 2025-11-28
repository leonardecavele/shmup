/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 00:17:01 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/29 00:18:14 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#define TARGET_FRAME_TIME 1 / 60

void	sleep_remaining(double time);
double	get_time(void);
