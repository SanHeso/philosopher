/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosoph.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnewman <hnewman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 16:01:36 by hnewman           #+#    #+#             */
/*   Updated: 2021/07/13 19:55:24 by hnewman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPH_H
# define PHILOSOPH_H
# include "stdio.h"
# include "unistd.h"
# include "pthread.h"
# include "stdlib.h"
# include "string.h"
# include "sys/time.h"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"

typedef struct s_phlsph	t_phlsph;

typedef struct s_all
{
	int				num_of_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long			time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	t_phlsph		*phil;
}					t_all;

typedef struct s_phlsph
{
	int				id;
	int				dead;
	int				c_eat;
	int				c_get;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_t		thread;
	t_all			*all;
	int				last;
}					t_phlsph;

int					ft_atoi_mod(char *str);
int					error(void *str);
void				init_param(t_all *all);
long				get_time(long begin);
void				ft_usleep(int time);
int					ft_strlen(char *str);
int					parser(int argc, char **argv, t_all *all);
t_phlsph			init_phlsph(t_all *all, int i);
void				memfree(t_all *all);
void				*check(void *arr);
int					check_die(t_all *all, int i);
void				status(t_phlsph *phil, char *color, char *str);
void				*life_of_a_phil(void *arr);
void				distr_fork(t_phlsph *phil, pthread_mutex_t *fork);
int					philo_lunch_begin(t_all *all);
void				ft_putnbr(int nb);

#endif