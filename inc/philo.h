/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:19:57 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/01 16:25:14 by tcampbel         ###   ########.fr       */
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
# define MTX_LOCK_ERR "mutex failed to lock\n"
# define MTX_ULOCK_ERR "mutex failed to unlock\n"
# define MTX_INIT_ERR "mutex failed to initialise\n"
# define MTX_DESTROY_ERR "mutex failed to destory\n"
# define PTHREAD_CR_ERR "failed to create thread\n"
# define PTHREAD_JOIN_ERR "failed to join thread\n"
# define TIME_ERR "failed to get time\n"
# define ARG_ERR "invalid arg\n"
# define ARG_SIZE_ERR "int max exceeded\n"
# define ARG_COUNT_ERR "invalid arg amount\n"
# define MALLOC_ERR "failed to allocate memory\n"
# define MEAL_COUNT_ERR "meal count is zero, boooooo!\n"

typedef pthread_mutex_t t_mutex;
typedef struct s_table t_table;

typedef enum e_ph_status
{
	L_FORK,
	R_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
}	t_ph_status;

typedef enum e_bool
{
	true = 1,
	false = 0,
}	t_bool;

typedef struct s_fork
{
	t_mutex	fork;	
	long	fork_id;
}	t_fork;

typedef struct s_philo
{
	pthread_t	thread;
	long		id;
	long		meals_eaten;
	long		last_meal_time;
	t_bool		full;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_mutex		full_lock;
	t_mutex		meals_eaten_lock;
	t_mutex		last_meal_time_lock;
	t_table		*table;	
}	t_philo;

typedef struct s_table
{
	long		ph_num;
	long		start_time;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		meal_count;
	t_bool		end_dinner;
	t_mutex		dead_lock;
	t_philo		*ph;
	t_fork		*forks;
	pthread_t	waiter;
}	t_table;

long		ft_atol(const char *str);
int			ft_strlen(char *str);
int			check_args(char **av);
int			init_structs(t_table *table, char **av);
int			start_dinner(t_table *table);
int			ft_perror(char *str);
long		get_time(void);
void		precise_usleep(long time);
int			print_status(t_philo *ph, t_ph_status status);


#endif
