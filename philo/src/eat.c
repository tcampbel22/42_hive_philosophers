/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:09:08 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/04 14:58:40 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	pick_up_forks(t_philo *ph)
{
	if (ph->id % 2 == 0)
	{
		pthread_mutex_lock(&ph->left_fork->fork);
		print_status(ph, L_FORK);
		pthread_mutex_lock(&ph->right_fork->fork);
		print_status(ph, R_FORK);
	}
	else
	{
		usleep(ph->table->time_to_eat);
		pthread_mutex_lock(&ph->right_fork->fork);
		print_status(ph, R_FORK);
		pthread_mutex_lock(&ph->left_fork->fork);
		print_status(ph, L_FORK);
	}
	return (EXIT_SUCCESS);
}

static int	set_last_meal_time(t_philo *ph)
{
	pthread_mutex_lock(&ph->last_meal_time_lock);
	ph->last_meal_time = get_time() - ph->table->start_time;
	pthread_mutex_unlock(&ph->last_meal_time_lock);
	return (EXIT_SUCCESS);
}

static int	set_meals_eaten(t_philo *ph)
{
	pthread_mutex_lock(&ph->meals_eaten_lock);
	ph->meals_eaten++;
	pthread_mutex_lock(&ph->full_lock);
	if (ph->meals_eaten >= ph->table->meal_count)
		ph->full = true;
	pthread_mutex_unlock(&ph->full_lock);
	pthread_mutex_unlock(&ph->meals_eaten_lock);
	return (EXIT_SUCCESS);
}

static int	put_down_forks(t_philo *ph)
{
	pthread_mutex_unlock(&ph->left_fork->fork);
	pthread_mutex_unlock(&ph->right_fork->fork);
	return (EXIT_SUCCESS);
}

int	ph_eat(t_philo *ph)
{
	pick_up_forks(ph);
	set_last_meal_time(ph);
	print_status(ph, EATING);
	precise_usleep(ph->table->time_to_eat);
	if (ph->table->meal_count > 0)
		set_meals_eaten(ph);
	put_down_forks(ph);
	return (EXIT_SUCCESS);
}
