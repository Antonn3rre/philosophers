/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:12:36 by agozlan           #+#    #+#             */
/*   Updated: 2024/12/28 15:42:02 by agozlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct	s_general
{
	long int	begin; // get begin time with gettimeofday
	int	nb_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;  //initialize at -1
	pthread_mutex_t	print;
}	t_general;

typedef struct	s_philo
{
//	int	nb_of_philo;
	int	num;
	long int	last_eat;
	int	sleeping; //bool
	int	eating; //bool
	int	thinking; //bool
	int	dead;  // a initialiser
	int	times_eaten;
	pthread_t	thread;
	pthread_mutex_t	lock;
	int	l_f;
	int	r_f;
}	t_philo;

typedef struct	s_fork
{
	pthread_mutex_t	lock;
	int	status;
}	t_fork;

typedef struct s_total
{
	t_philo **philo;
	t_general	*gen;
	int	actual;
	t_fork	**fork;
}	t_total;

typedef struct	s_thread_data
{
	t_total *total;
	int	philo_index;
}	t_thread_data;

// main.c
void	*beginning(void *arg);
int main(int argc, char **argv);

// check.c
int	check_dead(t_philo *philo, t_general gen);
int	check_finished(t_philo **philo, t_general gen);
int	check_fork(int l_f, int r_f, t_fork **fork);

// free.c
void	free_struct(t_philo **philo, int num);
void	finishing(t_general gen, t_philo **philo, t_fork **fork, t_total *total);

// init.c
t_general	init_gen(int argc, char **argv);
t_fork	**create_fork(t_general gen);
t_philo	**create_philo(t_general gen);
t_philo		*init_philo(t_general gen, int i);
int	create_thread(t_total *total, int nb_philo);

// utils.c
int	ft_atoi(const char *nptr);
long int	get_time(void);

// action.c
void	eating(t_general *gen, t_philo *philo, t_fork **fork);
void	sleeping(t_general *gen, t_philo *philo);

#endif
