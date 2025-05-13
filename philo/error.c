/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <agozlan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:34:14 by agozlan           #+#    #+#             */
/*   Updated: 2025/02/27 17:06:06 by agozlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_time(pthread_mutex_t *print)
{
	pthread_mutex_lock(print);
	printf("Erreur fonction gettimeofday\n");
	pthread_mutex_unlock(print);
}

void	error_arg(void)
{
	printf("Expected, with pos nb : ./philo nb_of_philo");
	printf(" time_to_die time_to_eat time_to_sleep [nb_of_times_must_eat]\n");
}
