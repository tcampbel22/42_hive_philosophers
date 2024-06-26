/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:19:57 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/26 15:02:34 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>


typedef struct s_philo
{
	pthread_t	thread;
	size_t		id;
	int			ph_num;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		x_eat;
}	t_philo;

typedef struct s_data
{
	t_philo			*ph;
	pthread_mutex_t	*forks;	
}	t_data;

int			ft_atoi(const char *str);
int			ft_is_num(char c);
int			check_args(char **av);
pthread_t	create_thread(pthread_t thread);
int			init_philo_struct(char **av, t_philo *ph);
int			init_mutex(t_data  *data);
int			init_data_struct(t_data *t_data, char **av);
pthread_t	create_thread(pthread_t thread);
int			ft_perror(char *str);


#endif
