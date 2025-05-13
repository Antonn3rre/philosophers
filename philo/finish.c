/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:01:18 by agozlan           #+#    #+#             */
/*   Updated: 2025/02/25 15:22:55 by agozlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_struct(t_philo **philo, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (philo[i])
		{
			pthread_mutex_destroy(&philo[i]->lock);
			free(philo[i]);
		}
		i++;
	}
	free(philo);
}

void	free_fork(t_fork **fork, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&fork[i]->lock);
		free(fork[i]);
		i++;
	}
	free(fork);
}

void	finishing(t_philo **phi, t_fork **f, t_total *tt, t_mut *mut)
{
	int	i;

	i = 0;
	if (phi)
	{
		while (i < tt->gen.nb_of_philo)
		{
			pthread_join(tt->philo[i]->thread, NULL);
			i++;
		}
	}
	if (f)
		free_fork(f, tt->gen.nb_of_philo);
	if (phi)
		free_struct(phi, tt->gen.nb_of_philo);
	if (mut)
	{
		pthread_mutex_destroy(&mut->print);
		pthread_mutex_destroy(&mut->th_end);
		pthread_mutex_destroy(&mut->think);
		free(mut);
	}
	if (tt)
		free(tt);
}

void	fail_thread(t_total *total, int nb_philo, int i)
{
	int	j;

	j = 0;
	pthread_mutex_lock(&total->mut->th_end);
	total->mut->end = 1;
	pthread_mutex_unlock(&total->mut->th_end);
	j = 0;
	while (j < i)
	{
		pthread_join(total->philo[j]->thread, NULL);
		j++;
	}
	free_struct(total->philo, nb_philo);
}

int	end(t_mut *mut)
{
	pthread_mutex_lock(&mut->th_end);
	if (mut->end == 1)
	{
		pthread_mutex_unlock(&mut->th_end);
		return (1);
	}
	pthread_mutex_unlock(&mut->th_end);
	return (0);
}
