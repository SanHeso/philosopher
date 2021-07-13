/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnewman <hnewman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 19:37:59 by hnewman           #+#    #+#             */
/*   Updated: 2021/07/13 20:00:21 by hnewman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosoph.h"

void	status(t_phlsph *phil, char *color, char *str)
{
	long	time;

	time = get_time(phil->all->time);
	pthread_mutex_lock(&phil->all->print);
	printf("%s%lu %d %s\n", color, time, phil->id + 1, str);
	if (!phil->dead)
		pthread_mutex_unlock(&phil->all->print);
}

int	check_die(t_all *all, int i)
{
	long	time;

	time = get_time(all->time);
	while (all->phil[i].last + all->time_to_die < time)
	{
		all->phil[i].dead = 1;
		status(&all->phil[i], RED, "Death");
		memfree(all);
		return (0);
	}
	return (1);
}

void	*check(void *arr)
{
	int		i;
	int		j;
	t_all	*all;

	all = (t_all *)arr;
	while (1)
	{
		i = 0;
		j = 0;
		while (i < all->num_of_phil)
		{
			if (!check_die(all, i))
				return (NULL);
			j += all->phil[i].c_get;
			i++;
		}
		if (j == all->num_of_phil)
		{
			memfree(all);
			return (NULL);
		}
	}
	return (NULL);
}

void	*life_of_a_phil(void *arr)
{
	t_phlsph	*phil;

	phil = (t_phlsph *)arr;
	while (1)
	{
		pthread_mutex_lock(phil->left);
		status(phil, GREEN, "took the left fork");
		pthread_mutex_lock(phil->right);
		status(phil, GREEN, "took the right fork");
		status(phil, YELLOW, "having dinner");
		phil->last = get_time(phil->all->time);
		phil->c_eat++;
		if (phil->c_eat == phil->all->must_eat)
			phil->c_get = 1;
		ft_usleep(phil->all->time_to_eat);
		pthread_mutex_unlock(phil->left);
		pthread_mutex_unlock(phil->right);
		status(phil, BLUE, "sleeping");
		ft_usleep(phil->all->time_to_sleep);
		status(phil, MAGENTA, "thinking");
	}
	return (NULL);
}
