/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:22:38 by agozlan           #+#    #+#             */
/*   Updated: 2025/02/27 17:33:58 by agozlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	sleeping(t_general gen, t_mut *mut, t_philo *philo)
{
	long int	time;

	pthread_mutex_lock(&mut->print);
	time = get_time(gen);
	if (time == -1)
		return (-1);
	if (!end(mut))
		printf("%ld %d is sleeping\n", time, philo->num);
	pthread_mutex_unlock(&mut->print);
	if (go_usleep(gen.time_to_sleep) == -1)
		return (-1);
	return (0);
}

static int	eating(t_general gen, t_philo *philo, t_fork **fork, t_mut *mut)
{
	long int	time;

	lock(philo, fork, &pthread_mutex_lock);
	fork[philo->l_f]->status = 1;
	if (take_fork(gen, mut, philo) == -1)
		return (-1);
	fork[philo->r_f]->status = 1;
	if (take_fork(gen, mut, philo) == -1)
		return (-1);
	if (end(mut))
		return (lock(philo, fork, &pthread_mutex_unlock), 1);
	if (change_phi_stat(philo, gen) == -1)
		return (-1);
	pthread_mutex_lock(&mut->print);
	time = get_time(gen);
	if (!end(mut))
		printf("%ld %d is eating\n", time, philo->num);
	pthread_mutex_unlock(&mut->print);
	lock(philo, fork, &pthread_mutex_unlock);
	if (go_usleep(gen.time_to_eat) == -1)
		return (-1);
	if (after_eat(philo, fork, mut) == 0)
		return (0);
	return (sleeping(gen, mut, philo));
}

static int	living(t_total *total, int i)
{
	int	tmp;

	if (end(total->mut))
		return (1);
	if (total->gen.nb_of_philo % 2 == 1
		&& total->gen.time_to_eat >= total->gen.time_to_sleep)
	{
		tmp = forced_think(total, i);
		if (tmp == -1)
			return (-1);
		if (tmp == 1)
			return (1);
	}
	if (check_fork(total->philo[i]->l_f, total->philo[i]->r_f, total->fork))
	{
		tmp = eating(total->gen, total->philo[i], total->fork, total->mut);
		if (tmp == -1 || tmp == 1)
			return (tmp);
	}
	else
	{
		if (thinking(total, i, 1) == -1)
			return (-1);
	}
	return (0);
}

int	cycle_of_life(t_total *total, int i)
{
	int	result;

	result = living(total, i);
	if (result == -1)
	{
		pthread_mutex_lock(&total->mut->th_end);
		total->mut->end = 1;
		pthread_mutex_unlock(&total->mut->th_end);
		return (error_time(&total->mut->print), 0);
	}
	else if (result == 1)
		return (1);
	return (0);
}

void	*begin(void *arg)
{
	t_thread_data	*data;
	t_total			*total;
	int				i;
	int				result;

	data = (t_thread_data *)arg;
	total = data->total;
	i = data->philo_index;
	free(data);
	if (total->philo[i]->num % 2 == 1)
	{
		if (thinking(total, i, total->gen.time_to_eat) == -1)
			return ((void *)-1);
	}
	while (1)
	{
		result = cycle_of_life(total, i);
		if (result == -1)
			return ((void *)-1);
		if (result == 1)
			return ((void *)1);
		usleep(50);
	}
	return ((void *)1);
}
