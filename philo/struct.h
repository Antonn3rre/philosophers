/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <agozlan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:47:35 by agozlan           #+#    #+#             */
/*   Updated: 2025/02/25 16:54:33 by agozlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_general
{
	long int	begin;
	int			nb_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
}	t_general;

typedef struct s_mut
{
	int				end;
	pthread_mutex_t	th_end;
	pthread_mutex_t	print;
	pthread_mutex_t	think;
	int				must_think;
}	t_mut;	

typedef struct s_philo
{
	int				num;
	long int		last_eat;
	int				sleeping;
	int				eating;
	int				thinking;
	int				dead;
	int				times_eaten;
	pthread_t		thread;
	pthread_mutex_t	lock;
	int				l_f;
	int				r_f;
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t	lock;
	int				status;
}	t_fork;

typedef struct s_total
{
	t_philo		**philo;
	t_general	gen;
	int			actual;
	t_fork		**fork;
	t_mut		*mut;
}	t_total;

typedef struct s_thread_data
{
	t_total	*total;
	int		philo_index;
}	t_thread_data;

#endif
