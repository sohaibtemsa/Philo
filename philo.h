/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:04:10 by stemsama          #+#    #+#             */
/*   Updated: 2023/03/07 17:08:03 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_data
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_eat_fr_each;
	long long		start_time;
	// int		all_eat;
	int				is_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	// pthread_mutex_t	forks;
	struct s_philo	*philo;
}	t_data;

typedef struct s_philo
{
	int		id;
	int		l_f;
	int		r_f;
	int		nb_of_eat;
	long long		last_eat;
	pthread_t	thread_nb;
	t_data	*data;
}	t_philo;


//-----------------------------------------------------------> Parsing.c
void	pars(int ac, char **av);
int		ft_atoi(char *str);

//-----------------------------------------------------------> free_error.c
void	affiche_er(void);
void	ft_lstclear_double(char **lstmap);

//-----------------------------------------------------------> tools1.c
long long	ft_gettime();
void	mute_write(t_data *data, char *str, int nb_philo);

//-----------------------------------------------------------> tools2.c

#endif