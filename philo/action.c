/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:22:38 by agozlan           #+#    #+#             */
/*   Updated: 2024/12/28 17:56:26 by agozlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_general *gen, t_philo *philo, t_fork **fork)
{
		pthread_mutex_lock(&fork[philo->r_f]->lock);
		fork[philo->r_f]->status = 1;
		pthread_mutex_unlock(&fork[philo->r_f]->lock);
				
		pthread_mutex_lock(&gen->print);
		printf("%ld %d  has taken a fork\n", get_time(), philo->num);
		pthread_mutex_unlock(&gen->print);
	
		pthread_mutex_lock(&fork[philo->l_f]->lock);
		fork[philo->r_f]->status = 1;
		pthread_mutex_unlock(&fork[philo->l_f]->lock);
		pthread_mutex_lock(&gen->print);
		printf("%ld %d  has taken a fork\n", get_time(), philo->num);
		printf("%ld %d is eating\n", get_time(), philo->num);
		pthread_mutex_unlock(&gen->print);
		
		pthread_mutex_lock(&philo->lock);
		philo->last_eat = get_time();
		philo->eating = 1;
		philo->thinking = 0;
		pthread_mutex_unlock(&philo->lock);
		
		usleep(gen->time_to_eat * 1000);
		
		pthread_mutex_lock(&fork[philo->l_f]->lock);
		fork[philo->l_f]->status = 0;
		pthread_mutex_unlock(&fork[philo->l_f]->lock);
		
		pthread_mutex_lock(&fork[philo->r_f]->lock);
		fork[philo->r_f]->status = 0;
		pthread_mutex_unlock(&fork[philo->r_f]->lock);
		
		pthread_mutex_lock(&philo->lock);
		philo->eating = 0;
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->lock);
		sleeping(gen, philo);
}  // le 0 a 1 ne sert a rien parce que je ne delock pas entre, donc je ne pourrais jamais lire 1, soit travailler juste avec mutex, soit delock entre chaque changement de statut

void	sleeping(t_general *gen, t_philo *philo)
{
		pthread_mutex_lock(&philo->lock);
		philo->sleeping = 1;
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_lock(&gen->print);
		printf("%ld %d is sleeping\n", get_time(), philo->num);
		pthread_mutex_unlock(&gen->print);
		usleep(gen->time_to_sleep * 1000);
		pthread_mutex_lock(&philo->lock);
		philo->sleeping = 0;
		pthread_mutex_unlock(&philo->lock);
}
