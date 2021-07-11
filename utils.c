/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnewman <hnewman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 19:02:13 by hnewman           #+#    #+#             */
/*   Updated: 2021/07/11 18:11:10 by hnewman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosoph.h"

int	ft_atoi_mod(char *str)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	if (!str)
		return (-1);
	if (str[i] == '-' && str[i] == '+')
		return (-1);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			u = u * 10 + (str[i] - '0');
			i++;
		}
		else
			return (-1);
	}
	return (u);
}

int	error(void *str)
{
	write(1, str, ft_strlen(str));
	return (0);
}

long	get_time(long begin)
{
	long			time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time - begin);
}

void	ft_usleep(int time)
{
	time_t	begin;
	time_t	end;

	begin = get_time(0);
	end = get_time(0) + time;
	while (begin < end)
	{
		usleep(10);
		begin = get_time(0);
	}
}
