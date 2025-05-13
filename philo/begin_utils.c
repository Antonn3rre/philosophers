/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:25:25 by agozlan           #+#    #+#             */
/*   Updated: 2025/02/27 17:14:16 by agozlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	after_eat(t_philo *philo, t_fork **fork, t_mut *mut)
{
	lock(philo, fork, &pthread_mutex_lock);
	fork[philo->r_f]->status = 0;
	fork[philo->l_f]->status = 0;
	pthread_mutex_lock(&philo->lock);
	philo->eating = 0;
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->lock);
	lock(philo, fork, &pthread_mutex_unlock);
	if (end(mut))
		return (0);
	return (1);
}

int	change_phi_stat(t_philo *philo, t_general gen)
{
	long int	time;

	pthread_mutex_lock(&philo->lock);
	time = get_time(gen);
	if (time == -1)
		return (-1);
	philo->last_eat = time;
	philo->eating = 1;
	philo->thinking = 0;
	pthread_mutex_unlock(&philo->lock);
	return (1);
}

int	take_fork(t_general gen, t_mut *mut, t_philo *philo)
{
	long int	time;

	pthread_mutex_lock(&mut->print);
	time = get_time(gen);
	if (time == -1)
		return (-1);
	if (!end(mut))
		printf("%ld %d  has taken a fork\n", time, philo->num);
	pthread_mutex_unlock(&mut->print);
	return (1);
}

int	forced_think(t_total *total, int i)
{
	int	tmp;

	tmp = 0;
	pthread_mutex_lock(&total->mut->think);
	if (total->mut->must_think == i)
		tmp = 1;
	pthread_mutex_unlock(&total->mut->think);
	if (tmp == 1)
	{
		pthread_mutex_lock(&total->mut->think);
		if (i == 0)
			total->mut->must_think = total->gen.nb_of_philo - 1;
		else
			total->mut->must_think--;
		pthread_mutex_unlock(&total->mut->think);
		if (thinking(total, i, total->gen.time_to_eat) == -1)
			return (-1);
		if (end(total->mut))
			return (1);
	}
	return (0);
}

int	thinking(t_total *total, int i, int time_think)
{
	long int	time;

	pthread_mutex_lock(&total->philo[i]->lock);
	if (!total->philo[i]->thinking)
	{
		total->philo[i]->thinking = 1;
		pthread_mutex_lock(&total->mut->print);
		time = get_time(total->gen);
		if (time == -1)
			return (-1);
		if (!end(total->mut))
			printf("%ld %d is thinking\n", time, total->philo[i]->num);
		pthread_mutex_unlock(&total->mut->print);
	}
	pthread_mutex_unlock(&total->philo[i]->lock);
	usleep(time_think * 1000);
	return (0);
}
