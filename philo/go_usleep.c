/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <agozlan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:09:30 by agozlan           #+#    #+#             */
/*   Updated: 2025/02/25 15:44:25 by agozlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long int	get_time_ms(void)
{
	struct timeval	current_t;
	long int		time;

	if (gettimeofday(&current_t, NULL) == -1)
		return (-1);
	time = (current_t.tv_sec * 1000) + (current_t.tv_usec / 1000);
	return (time);
}

int	go_usleep(long int to_sleep)
{
	long int	start;

	start = get_time_ms();
	if (start == -1)
		return (-1);
	while (get_time_ms() - start < to_sleep)
		usleep(50);
	return (1);
}
