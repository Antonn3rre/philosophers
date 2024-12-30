/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agozlan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:09:28 by agozlan           #+#    #+#             */
/*   Updated: 2024/12/30 13:57:51 by agozlan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

long int	get_time(void)
{
	struct timeval current_t;

	if (gettimeofday(&current_t, NULL) == -1)
		return (-1);
	return (current_t.tv_sec * 1000) + (current_t.tv_usec / 1000);
}
