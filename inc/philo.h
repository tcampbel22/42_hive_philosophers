/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:19:57 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/27 16:28:35 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define INT_MAX 2147483647

typedef struct s_data t_data;

typedef struct s_fork
{
	pthread_mutex_t	*forks;	
	size_t			fork_id;
}	t_fork;

typedef struct s_philo
{
	pthread_t	thread;
	size_t		id;
	t_data		*waiter;
}	t_philo;

typedef struct s_data
{
	t_philo	*ph;
	t_fork	*fork;
	long	ph_num;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		meal_count;
}	t_data;

long		ft_atol(const char *str);
int			ft_is_num(char c);
int			check_args(char **av);
pthread_t	create_thread(pthread_t thread);
int			init_philo_struct(char **av, t_philo *ph, long ph_num);
int			init_mutex(t_data  *waiter);
int			init_data_struct(t_data  *waiter, char **av);
pthread_t	create_thread(pthread_t thread);
int			ft_perror(char *str);


#endif
