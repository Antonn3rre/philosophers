/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:09:28 by agozlan           #+#    #+#             */
/*   Updated: 2025/02/27 16:58:08 by agozlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi_phi(char *str)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	while (str[i])
	{
		if (i == 10 || !ft_isnum(str[i]))
			return (-1);
		num = num * 10 + (str[i] - 48);
		i++;
		if (num > 2147483647)
			return (-1);
	}
	return ((int)num);
}
/*
int	ft_atoi(const char *nptr)
{
	int	num;
	int	i;
	int	impair;

	num = 0;
	i = 0;
	impair = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			impair = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - 48);
		i++;
	}
	return (num * impair);
}
*/

long int	get_time(t_general gen)
{
	struct timeval	current_t;
	long int		time;

	if (gettimeofday(&current_t, NULL) == -1)
		return (-1);
	time = (current_t.tv_sec * 1000) + (current_t.tv_usec / 1000);
	return (time - gen.begin);
}

void	lock(t_philo *phi, t_fork **f, int (*un_lock)(pthread_mutex_t *))
{
	if (phi->l_f < phi->r_f)
	{
		un_lock(&f[phi->l_f]->lock);
		un_lock(&f[phi->r_f]->lock);
	}
	else
	{
		un_lock(&f[phi->r_f]->lock);
		un_lock(&f[phi->l_f]->lock);
	}
}
