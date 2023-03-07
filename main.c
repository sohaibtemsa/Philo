/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:03:10 by stemsama          #+#    #+#             */
/*   Updated: 2023/03/07 18:10:11 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	long long	n;
	int			i;

	n = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] <= '9' && str[i] >= '0')
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	if (str[i] || n > 2147483647)
		return (0);
	return (n);
}

void	pars(int ac, char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (ft_atoi(av[i]) == 0)
			affiche_er();
	}
}

void init_data(t_data *data, char **av)
{
	data->nb_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if(av[5])
		data->nb_of_eat_fr_each = ft_atoi(av[5]);
	else
		data->nb_of_eat_fr_each = 0;
}

int	init_philo(t_data *data)
{
	int			nb;

	nb = data->nb_of_philo;
	data->philo = malloc(sizeof(pthread_t) * nb);
	while (--nb >= 0)
	{
		data->philo[nb].id = nb;
		data->philo[nb].nb_of_eat = 0;
		data->philo[nb].l_f = nb;
		data->philo[nb].r_f = (nb - 1) % data->nb_of_philo;
		data->philo[nb].last_eat = 0;
		data->philo[nb].data = data;
	}
	return (1);
}

int	init_mutex(t_data *data)
{
	int	nb;

	nb = data->nb_of_philo;
	data->forks = malloc(sizeof(pthread_mutex_t) * nb);
	while (--nb >= 0)
	{
		if (pthread_mutex_init(&(data->forks[nb]), NULL) != 0)
			return (0);
	}
	if (pthread_mutex_init(&(data->write), NULL) != 0)
		return (0);
	// if (pthread_mutex_init(&(data->write), NULL) != 0)
	// 	return (0);
	return (1);
}

void	eat(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->l_f]));
	mute_write(data, "has taken a left fork" ,philo->id + 1);
	pthread_mutex_lock(&(data->forks[philo->r_f]));
	mute_write(data, "has taken a right fork" ,philo->id + 1);
	mute_write(data, "is eating" ,philo->id + 1);
	pthread_mutex_unlock(&(data->forks[philo->l_f]));
	pthread_mutex_unlock(&(data->forks[philo->r_f]));
}

void *fun_first(void *philoo)
{
	t_philo	*philo;
	t_data	*data;
	int		is_dead;

	philo = (t_philo *)philoo;
	data = philo->data;
	is_dead = data->is_dead;
	if (philo->id % 2 != 0)
		usleep(1000);
	while (1)
	{
		eat(philo);
	}
	
}

int	go(t_data *data)
{
	int 	cnt;
	t_philo	*philo;

	cnt = -1;
	philo = data->philo;
	data->start_time = ft_gettime();
	while (++cnt < data->nb_of_philo)
	{
		philo[cnt].last_eat = ft_gettime();
		if ((pthread_create(&(philo[cnt].thread_nb), NULL, fun_first, &philo[cnt]) != 0))
			return (0);
		pthread_detach(philo[cnt].thread_nb);
	}
	return (1);
}

void	all_eat_or_die(t_data *data)
{
}

int	main(int ac, char** av)
{
	t_data	data;
	char	*strarg;
	char	**lstarg;

	if (ac != 5 && ac != 6)
		affiche_er();
	pars(ac, av);
	init_data(&data, av);
	if (init_philo(&data) == 0 || init_mutex(&data) == 0)
		affiche_er();
	if (!go(&data))
		affiche_er();
	all_eat_or_die(&data);
	while (1)
		;
}
