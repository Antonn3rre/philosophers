/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:10:21 by agozlan           #+#    #+#             */
/*   Updated: 2024/12/30 15:42:19 by agozlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*beginning(void *arg)
{
	t_thread_data	*data;
	t_total	*total;
	int	i;

	data = (t_thread_data *)arg;
	total = data->total;
	i = data->philo_index;
	free(data);
	if (total->philo[i]->num % 2 == 1)
		usleep(total->gen->time_to_eat);
	if (total->gen->nb_of_philo % 2 == 1 && i + 1 == total->gen->nb_of_philo)
		usleep(total->gen->time_to_eat * 2);
	while(1)
	{
		if (total->philo[i]->thinking == 0)
		{
			pthread_mutex_lock(&total->philo[i]->lock);
			total->philo[i]->thinking = 1;
			pthread_mutex_unlock(&total->philo[i]->lock);
			pthread_mutex_lock(&total->gen->print);
			printf("%ld %d is thinking\n", get_time(), total->philo[i]->num);
			pthread_mutex_unlock(&total->gen->print);
		}
		if (check_fork(total->philo[i]->l_f, total->philo[i]->r_f, total->fork))
			eating(total->gen, total->philo[i], total->fork);
		else
			usleep(10);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_general	gen;
	t_philo	**philo;
	t_fork	**fork;
	t_total	*total;
	int	i;

	if (argc < 5 || argc > 6)
		return (0);
	total = malloc(sizeof(t_total));
	if (!total)
		return (0);
	gen = init_gen(argc, argv);
	fork = create_fork(gen);
	if (!fork)
		return (0);
	pthread_mutex_init(&gen.print, NULL);
	philo = create_philo(gen);
	if (!philo)
		return (0);
	i = 0;
	total->philo = philo;
	total->gen = &gen;
	total->fork = fork;
	if (!create_thread(total, gen.nb_of_philo))
		return (0);
	while (!check_finished(philo, gen)) // avant ou apres pthread join ?
		usleep(10);
	finishing(gen, philo, fork, total);
	return (0);
}
