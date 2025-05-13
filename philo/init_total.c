/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_total.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:54:34 by agozlan           #+#    #+#             */
/*   Updated: 2025/02/27 16:57:25 by agozlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	**create_philo(t_general gen)
{
	t_philo	**philo;
	int		i;

	philo = malloc(gen.nb_of_philo * sizeof(t_philo *));
	if (!philo)
		return (NULL);
	i = 0;
	while (i < gen.nb_of_philo)
	{
		philo[i] = init_philo(gen, i);
		if (!philo[i])
		{
			free_struct(philo, gen.nb_of_philo);
			return (NULL);
		}
		i++;
	}
	return (philo);
}

static t_mut	*init_mut(void)
{
	t_mut	*mut;

	mut = malloc(sizeof(t_mut));
	if (!mut)
		return (NULL);
	mut->end = 0;
	if (pthread_mutex_init(&mut->print, NULL))
	{
		free(mut);
		return (NULL);
	}
	if (pthread_mutex_init(&mut->th_end, NULL))
	{
		pthread_mutex_destroy(&mut->print);
		free(mut);
		return (NULL);
	}
	if (pthread_mutex_init(&mut->think, NULL))
	{
		pthread_mutex_destroy(&mut->print);
		pthread_mutex_destroy(&mut->th_end);
		free(mut);
		return (NULL);
	}
	return (mut);
}

static t_fork	**create_fork(t_general gen)
{
	t_fork	**fork;
	int		i;

	fork = malloc(sizeof(t_fork *) * gen.nb_of_philo);
	if (!fork)
		return (NULL);
	i = 0;
	while (i < gen.nb_of_philo)
	{
		fork[i] = malloc(sizeof(t_fork));
		if (!fork[i])
		{
			free_fork(fork, i);
			return (NULL);
		}
		if (pthread_mutex_init(&fork[i]->lock, NULL))
		{
			free_fork(fork, i + 1);
			return (NULL);
		}
		fork[i]->status = 0;
		i++;
	}
	return (fork);
}

static t_general	init_gen(int argc, char **argv)
{
	struct timeval	tv;
	t_general		gen;

	gettimeofday(&tv, NULL);
	gen.begin = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	gen.nb_of_philo = ft_atoi_phi(argv[1]);
	gen.time_to_die = ft_atoi_phi(argv[2]);
	gen.time_to_eat = ft_atoi_phi(argv[3]);
	gen.time_to_sleep = ft_atoi_phi(argv[4]);
	if (argc == 6)
		gen.must_eat = ft_atoi_phi(argv[5]);
	else
		gen.must_eat = -1;
	return (gen);
}

t_total	*init_total(int argc, char **argv)
{
	t_total	*total;

	total = malloc(sizeof(t_total));
	if (!total)
		return (NULL);
	total->gen = init_gen(argc, argv);
	total->fork = create_fork(total->gen);
	if (!total->fork)
		return (finishing(NULL, NULL, total, NULL), NULL);
	total->mut = init_mut();
	if (!total->mut)
		return (finishing(NULL, total->fork, total, NULL), NULL);
	total->mut->must_think = total->gen.nb_of_philo - 1;
	total->philo = create_philo(total->gen);
	if (!total->philo)
		return (finishing(NULL, total->fork, total, total->mut), NULL);
	return (total);
}
