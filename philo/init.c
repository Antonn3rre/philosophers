/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:07:11 by agozlan           #+#    #+#             */
/*   Updated: 2024/12/28 15:50:04 by agozlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_general	init_gen(int argc, char **argv) // ok, ajouter verif ?
{
	struct timeval	tv;
	t_general		gen;

	gettimeofday(&tv, NULL);
	gen.begin = (tv.tv_sec * 1000) + (tv.tv_usec);
	gen.nb_of_philo = ft_atoi(argv[1]);
	gen.time_to_die = ft_atoi(argv[2]);
	gen.time_to_eat = ft_atoi(argv[3]);
	gen.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		gen.must_eat = ft_atoi(argv[5]);
	else
		gen.must_eat = -1;
	return (gen);
}

t_fork	**create_fork(t_general gen)
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
			// free les forks
			return (NULL);
		}
		pthread_mutex_init(&fork[i]->lock, NULL);
		fork[i]->status = 0;
		i++;
	}
	return (fork);
}

t_philo	**create_philo(t_general gen)
{
	t_philo	**philo;
	int		i;

	philo = malloc(gen.nb_of_philo * sizeof(t_philo *));
	if (!philo)
		return (NULL); // free les forks ?
	i = 0;
	while (i < gen.nb_of_philo)
	{
		philo[i] = init_philo(gen, i);
		if (!philo[i])
		{
			free_struct(philo, gen.nb_of_philo); // free forks ??
			return (NULL);
		}
		i++;
	}
	return (philo);
}

t_philo	*init_philo(t_general gen, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	pthread_mutex_init(&philo->lock, NULL);
	pthread_mutex_lock(&philo->lock);
	philo->num = i + 1;
	philo->last_eat = gen.begin;
	philo->sleeping = 0;
	philo->eating = 0;
	philo->thinking = 0;
	philo->times_eaten = 0;
	philo->dead = 0;
	philo->l_f = i;
	if (i + 1 == gen.nb_of_philo)
		philo->r_f = 0;
	else
		philo->r_f = i + 1;
	pthread_mutex_unlock(&philo->lock);
	return (philo);
}

int	create_thread(t_total *total, int nb_philo)
{
	t_thread_data	*data;
	int				i;

	i = 0;
	while (i < nb_philo)
	{
		data = malloc(sizeof(t_thread_data));
		if (!data)
		{
			free_struct(total->philo, nb_philo);
			return (0);
		}
		data->total = total;
		data->philo_index = i;
		if (pthread_create(&total->philo[i]->thread, NULL, beginning, (void *)data) != 0)
		{
			free(data);
			free_struct(total->philo, nb_philo);
			return (0);
		}
		i++;
	}
	return (1);
}
