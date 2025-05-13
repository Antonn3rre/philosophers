/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:40:47 by agozlan           #+#    #+#             */
/*   Updated: 2025/02/27 18:44:27 by agozlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_arg(t_general gen, char **argv)
{
	if (gen.time_to_die < 0 || gen.time_to_eat < 0 || gen.time_to_sleep < 0)
		return (error_arg(), 0);
	if (gen.nb_of_philo < 0)
		return (error_arg(), 0);
	if (argv[5])
	{
		if (ft_atoi_phi(argv[5]) < 0)
			return (error_arg(), 0);
	}
	return (1);
}

int	check_dead(t_philo *philo, t_general gen, t_mut *mut)
{
	long int	time;

	time = get_time(gen);
	if (time == -1)
		return (-1);
	if (time - philo->last_eat > gen.time_to_die)
	{
		pthread_mutex_lock(&mut->th_end);
		mut->end = 1;
		pthread_mutex_unlock(&mut->th_end);
		pthread_mutex_lock(&mut->print);
		printf("%ld %d died\n", time, philo->num);
		pthread_mutex_unlock(&mut->print);
		philo->dead = 1;
		return (1);
	}
	return (0);
}

int	check_end(t_philo **philo, t_general gen, t_mut *mut)
{
	int	i;
	int	finished;

	finished = 0;
	i = -1;
	while (++i < gen.nb_of_philo)
	{
		pthread_mutex_lock(&philo[i]->lock);
		if (check_dead(philo[i], gen, mut))
		{
			pthread_mutex_unlock(&philo[i]->lock);
			return (1);
		}
		if (gen.must_eat >= 0 && philo[i]->times_eaten >= gen.must_eat)
			finished++;
		pthread_mutex_unlock(&philo[i]->lock);
	}
	if (finished == gen.nb_of_philo)
	{
		pthread_mutex_lock(&mut->th_end);
		mut->end = 1;
		pthread_mutex_unlock(&mut->th_end);
		return (1);
	}
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
