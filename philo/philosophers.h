/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:12:36 by agozlan           #+#    #+#             */
/*   Updated: 2025/02/27 17:03:44 by agozlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# include "struct.h"

// philo.c
int			main(int argc, char **argv);
void		*one_philo(void *arg);

// check.c
int			check_arg(t_general gen, char **argv);
int			check_dead(t_philo *philo, t_general gen, t_mut *mut);
int			check_end(t_philo **philo, t_general gen, t_mut *mut);
int			check_fork(int l_f, int r_f, t_fork **fork);

// free.c
void		free_struct(t_philo **philo, int num);
void		free_fork(t_fork **fork, int num);
void		finishing(t_philo **phi, t_fork **f, t_total *tt, t_mut *mut);
void		fail_thread(t_total *total, int nb_philo, int i);
int			end(t_mut *mut);

// init_utils.c
t_philo		*init_philo(t_general gen, int i);

// init_total.c
t_total		*init_total(int argc, char **argv);

// utils.c
int			ft_atoi_phi(char *str);
long int	get_time(t_general gen);
void		lock(t_philo *phi, t_fork **f, int (*un_lock)(pthread_mutex_t *));

// go_usleep.c
int			go_usleep(long int to_sleep);

// begin.c
void		*begin(void *arg);

// begin_utils.c
int			after_eat(t_philo *philo, t_fork **fork, t_mut *mut);
int			change_phi_stat(t_philo *philo, t_general gen);
int			take_fork(t_general gen, t_mut *mut, t_philo *philo);
int			forced_think(t_total *total, int i);
int			thinking(t_total *total, int i, int time_think);

// error.c
void		error_time(pthread_mutex_t *print);
void		error_arg(void);

#endif
