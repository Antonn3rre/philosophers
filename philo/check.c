/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:40:47 by agozlan           #+#    #+#             */
/*   Updated: 2024/12/28 18:22:31 by agozlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_dead(t_philo *philo, t_general gen)
{
	long int	time;

	time = get_time();
	if (time - philo->last_eat > gen.time_to_die)
	{
		pthread_mutex_lock(&gen.print);
		printf("%ld %d died\n", time, philo->num);
		pthread_mutex_unlock(&gen.print);
		philo->dead = 1;
		return (1);
	}
	return (0);
}

int	check_finished(t_philo **philo, t_general gen)
{
	int	i;
	int	finished;

	finished = 0;
	i = 0;
	while (i < gen.nb_of_philo)
	{
		pthread_mutex_lock(&philo[i]->lock);
		if (check_dead(philo[i], gen))
		{
			pthread_mutex_unlock(&philo[i]->lock);
			return (1);
		}
		if (gen.must_eat >= 0 && philo[i]->times_eaten >= gen.must_eat)
			finished++;
		pthread_mutex_unlock(&philo[i]->lock);
		i++;
	}
	if (finished == gen.nb_of_philo)
		return (1);
	return (0);
}

int	check_fork(int l_f, int r_f, t_fork **fork)
{
	pthread_mutex_lock(&fork[l_f]->lock);
	if (fork[l_f]->status == 1)
	{
		pthread_mutex_unlock(&fork[l_f]->lock);
		return (0);
	}
	pthread_mutex_unlock(&fork[l_f]->lock);
	pthread_mutex_lock(&fork[r_f]->lock);
	if (fork[r_f]->status == 1)
	{
		pthread_mutex_unlock(&fork[r_f]->lock);
		return (0);
	}
	pthread_mutex_unlock(&fork[r_f]->lock);
	return (1);
}
