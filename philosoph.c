/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosoph.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnewman <hnewman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 16:00:38 by hnewman           #+#    #+#             */
/*   Updated: 2021/07/11 19:18:53 by hnewman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosoph.h"

void	the_beginning_of_the_feast(t_phlsph *phil)
{
	pthread_t	t;
	int			i;

	i = 0;
	pthread_create(&t, NULL, check, phil->all);
	while (i < phil->all->num_of_phil)
	{
		pthread_create(&phil[i].thread, NULL, life_of_a_phil, &phil[i]);
		i += 2;
	}
	ft_usleep(100);
	i = 1;
	while (i < phil->all->num_of_phil)
	{
		pthread_create(&phil[i].thread, NULL, life_of_a_phil, &phil[i]);
		i += 2;
	}
	pthread_join(t, NULL);
}

void	distr_fork(t_phlsph *phil, pthread_mutex_t *fork)
{
	if (phil->id == phil->all->num_of_phil - 1)
	{
		phil->left = &fork[phil->id];
		phil->right = &fork[0];
	}
	else
	{
		phil->left = &fork[phil->id];
		phil->right = &fork[phil->id + 1];
	}
}

int	philo_lunch_begin(t_all *all)
{
	int	i;

	i = 0;
	all->time = get_time(0);
	all->fork = malloc(sizeof(pthread_mutex_t) * all->num_of_phil);
	if (!all->fork)
		return (0);
	while (i < all->num_of_phil)
	{
		pthread_mutex_init(&all->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&all->print, NULL);
	i = 0;
	all->phil = malloc(sizeof(t_phlsph) * all->num_of_phil);
	if (!all->phil)
		return (0);
	while (i < all->num_of_phil)
	{
		all->phil[i] = init_phlsph(all, i);
		distr_fork(&all->phil[i], all->fork);
		i++;
	}
	the_beginning_of_the_feast(all->phil);
	return (1);
}

int	parser(int argc, char **argv, t_all *all)
{
	int	i;
	int	val;

	i = 1;
	all->must_eat = -1;
	while (i < argc)
	{
		val = ft_atoi_mod(argv[i]);
		if (i == 1 && val != -1)
			all->num_of_phil = val;
		else if (i == 2 && val != -1)
			all->time_to_die = val;
		else if (i == 3 && val != -1)
			all->time_to_eat = val;
		else if (i == 4 && val != -1)
			all->time_to_sleep = val;
		else if (i == 5 && val != -1)
			all->must_eat = val;
		else
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_all	*all;

	all = malloc(sizeof(t_all));
	if (!all)
		return (0);
	if (argc == 5 || argc == 6)
	{
		if (parser(argc, argv, all))
		{
			if (!philo_lunch_begin(all))
				return (1);
		}
		else
			return (error("Error: Invalid argument!\n"));
	}
	else
		return (error("Error: More or less arguments!\n"));
}
