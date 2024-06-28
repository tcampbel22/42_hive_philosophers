/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:19:57 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/28 16:43:32 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define INT_MAX 2147483647
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef pthread_mutex_t t_mutex;
typedef struct s_table t_table;

typedef enum e_bool
{
	true = 1,
	false = 0,
}	t_bool;

typedef struct s_fork
{
	t_mutex	fork;	
	size_t	fork_id;
}	t_fork;

typedef struct s_philo
{
	pthread_t	thread;
	size_t		id;
	t_bool		full;
	size_t		meals_eaten;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_table		*table;	
}	t_philo;

typedef struct s_table
{
	t_philo		*ph;
	t_fork		*forks;
	long		ph_num;
	size_t		start_time;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			meal_count;
	t_bool		end_dinner;
	pthread_t	waiter;
}	t_table;

long		ft_atol(const char *str);
int			check_args(char **av);
int			init_structs(t_table *table, char **av);
int			start_dinner(t_table *table);
int			ft_perror(char *str);
size_t		get_time(t_table *table);


#endif
