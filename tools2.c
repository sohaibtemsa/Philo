/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:05:17 by stemsama          #+#    #+#             */
/*   Updated: 2023/03/07 10:34:40 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_lstclear_double(char **lstmap)
{
	int	i;

	i = 0;
	while (lstmap[i])
		free(lstmap[i++]);
	free(lstmap);
}

void	affiche_er(void)
{
	write(1, "Error\n", 6);
	exit (1);
}
