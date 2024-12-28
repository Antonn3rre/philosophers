/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:01:18 by agozlan           #+#    #+#             */
/*   Updated: 2024/12/28 15:41:38 by agozlan          ###   ########.fr       */
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

void	finishing(t_general gen, t_philo **philo, t_fork **fork, t_total *total)
{
	int	i;

	i = 0;
	while (i < gen.nb_of_philo)
	{
		pthread_detach(philo[i]->thread);
		i++;
	}
	i = 0;
	while (i < gen.nb_of_philo)
	{
		pthread_mutex_destroy(&fork[i]->lock);
		free(fork[i]);
		i++;
	}
	free(fork);
	free_struct(philo, gen.nb_of_philo);
	free(total);
	pthread_mutex_destroy(&gen.print);
}
