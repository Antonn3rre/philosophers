/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:10:21 by agozlan           #+#    #+#             */
/*   Updated: 2025/02/27 18:40:40 by agozlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_thread(t_total *total, int nb_philo)
{
	t_thread_data	*data;
	int				i;

	i = 0;
	while (i < nb_philo)
	{
		data = malloc(sizeof(t_thread_data));
		if (!data)
			return (fail_thread(total, nb_philo, i), 0);
		data->total = total;
		data->philo_index = i;
		if (pthread_create(&total->philo[i]->thread,
				NULL, begin, (void *)data) != 0)
			return (free(data), fail_thread(total, nb_philo, i), 0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_total	*total;

	if (argc < 5 || argc > 6)
		return (error_arg(), 0);
	total = init_total(argc, argv);
	if (!total || !check_arg(total->gen, argv))
		return (0);
	if (total->gen.nb_of_philo == 1)
	{
		pthread_create(&total->philo[0]->thread,
			NULL, one_philo, (void *)total);
		finishing(total->philo, total->fork, total, total->mut);
		return (0);
	}
	else if (!create_thread(total, total->gen.nb_of_philo))
	{
		finishing(NULL, total->fork, total, total->mut);
		return (0);
	}
	while (!check_end(total->philo, total->gen, total->mut))
		usleep(100);
	finishing(total->philo, total->fork, total, total->mut);
	return (0);
}

void	*one_philo(void *arg)
{
	t_total		*total;
	long int	time;

	total = (t_total *)arg;
	thinking(total, 0, total->gen.time_to_die);
	pthread_mutex_lock(&total->mut->print);
	time = get_time(total->gen);
	if (time == -1)
		return (NULL);
	printf("%ld 1 died\n", time);
	pthread_mutex_unlock(&total->mut->print);
	return (0);
}
