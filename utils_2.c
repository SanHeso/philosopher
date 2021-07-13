/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnewman <hnewman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 19:18:06 by hnewman           #+#    #+#             */
/*   Updated: 2021/07/12 19:22:42 by hnewman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosoph.h"

t_phlsph	init_phlsph(t_all *all, int i)
{
	t_phlsph	phil;

	phil.id = i;
	phil.dead = 0;
	phil.c_eat = 0;
	phil.c_get = 0;
	phil.all = all;
	phil.last = get_time(all->time);
	return (phil);
}

void	memfree(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->num_of_phil)
	{
		pthread_mutex_destroy(&all->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&all->print);
	free(all->fork);
	free(all->phil);
	free(all);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}