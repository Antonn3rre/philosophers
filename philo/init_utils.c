/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:07:11 by agozlan           #+#    #+#             */
/*   Updated: 2025/02/25 17:02:01 by agozlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*init_philo(t_general gen, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	if (pthread_mutex_init(&philo->lock, NULL))
	{
		free(philo);
		return (NULL);
	}
	pthread_mutex_lock(&philo->lock);
	philo->num = i + 1;
	philo->last_eat = gen.begin;
	philo->sleeping = 0;
	philo->eating = 0;
	philo->thinking = 0;
	philo->times_eaten = 0;
	philo->dead = 0;
	philo->l_f = i;
	philo->r_f = i + 1;
	if (i + 1 == gen.nb_of_philo)
		philo->r_f = 0;
	pthread_mutex_unlock(&philo->lock);
	return (philo);
}
