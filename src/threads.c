/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:32:02 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/01 17:42:16 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pick_up_forks(t_philo *ph)
{
	if (ph->id % 2 == 0)
	{
		if (pthread_mutex_lock(&ph->left_fork->fork))
			return (ft_perror(MTX_LOCK_ERR));
		print_status(ph, L_FORK);
		if (pthread_mutex_lock(&ph->right_fork->fork))
			return (ft_perror(MTX_LOCK_ERR));
		print_status(ph, R_FORK);
	}
	else
	{
		if (pthread_mutex_lock(&ph->right_fork->fork))
			return (ft_perror(MTX_LOCK_ERR));
		print_status(ph, R_FORK);
		if (pthread_mutex_lock(&ph->left_fork->fork))
			return (ft_perror(MTX_LOCK_ERR));
		print_status(ph, L_FORK);
	}
	return (EXIT_SUCCESS);
}
static int	set_last_meal_time(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->last_meal_time_lock))
		return (ft_perror(MTX_LOCK_ERR));
	ph->last_meal_time = get_time();
	if (pthread_mutex_unlock(&ph->last_meal_time_lock))
		return (ft_perror(MTX_ULOCK_ERR));
	return  (EXIT_SUCCESS);
}

static int	set_meals_eaten(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->meals_eaten_lock))
		return (ft_perror(MTX_LOCK_ERR));
	ph->meals_eaten++;
	if (pthread_mutex_lock(&ph->full_lock))
		return (ft_perror(MTX_LOCK_ERR));
	if (ph->meals_eaten >= ph->table->meal_count)
		ph->full = true;
	if (pthread_mutex_unlock(&ph->full_lock))
		return (ft_perror(MTX_ULOCK_ERR));
	if (pthread_mutex_unlock(&ph->meals_eaten_lock))
		return (ft_perror(MTX_ULOCK_ERR));
	return (EXIT_SUCCESS);
}

static int	put_down_forks(t_philo *ph)
{
	if (pthread_mutex_unlock(&ph->left_fork->fork))
		return (ft_perror(MTX_ULOCK_ERR));
	if (pthread_mutex_unlock(&ph->right_fork->fork))
		return (ft_perror(MTX_ULOCK_ERR));
	return (EXIT_SUCCESS);
}

static void	ph_sleep(t_philo *ph)
{
	print_status(ph, SLEEPING);
	usleep(ph->table->time_to_sleep);
}

int	ph_eat(t_philo *ph)
{
	if (pick_up_forks(ph))
		return (EXIT_FAILURE);
	if (set_last_meal_time(ph))
		return (EXIT_FAILURE);
	print_status(ph, EATING);
	usleep(ph->table->time_to_eat);
	if (set_meals_eaten(ph))
		return (EXIT_FAILURE);
	if (put_down_forks(ph))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	*dinner(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (ph->table->end_dinner == false)
	{
		if (ph->full == true)
			break ;
		ph_eat(ph);
		ph_sleep(ph);
		//think(ph);
	}
	return (NULL);
}

int	create_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->ph_num)
		if (pthread_create(&table->ph[i].thread, NULL, &dinner, &table->ph[i]))
			return(ft_perror(PTHREAD_CR_ERR));
	i = -1;
	while (++i < table->ph_num)
		if (pthread_join(table->ph[i].thread, NULL))
			return(ft_perror(PTHREAD_JOIN_ERR));
	return (EXIT_SUCCESS);
}

int	start_dinner(t_table *table)
{
	if (table->meal_count == 0)
		return (ft_perror(MEAL_COUNT_ERR));
	if (table->ph_num == 1)
		return (ft_perror("philo died\n")); //TODO 
	table->start_time = get_time();
	if(table->start_time == 1)
		return (EXIT_FAILURE);
	if (create_threads(table))
		return (EXIT_FAILURE);
	if (pthread_create(&table->waiter, NULL, &dinner, NULL))
		return (ft_perror(PTHREAD_CR_ERR));
	return(EXIT_SUCCESS);
}
