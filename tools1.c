/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:24:22 by stemsama          #+#    #+#             */
/*   Updated: 2023/03/07 17:10:59 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_gettime()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	mute_write(t_data *data, char *str, int nb_philo)
{
	pthread_mutex_lock(&data->write);
	printf("%lld %d %s\n",ft_gettime() - data->start_time, nb_philo, str);
	pthread_mutex_unlock(&data->write);
}

// int main()
// {
// 	long long n;

// 	n = ft_gettime();
// 	printf("%lld\n", n);
// 	usleep(100000);
// 	n = ft_gettime() - n;
// 	printf("%lld\n", n);
// }