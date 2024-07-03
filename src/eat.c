/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:09:08 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/03 10:27:08 by tcampbel         ###   ########.fr       */
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
	{
		printf("%li is now full\n", ph->id); //TESTING
		ph->full = true;
	}
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

int	ph_eat(t_philo *ph)
{
	if (pick_up_forks(ph))
		return (EXIT_FAILURE);
	if (set_last_meal_time(ph))
		return (EXIT_FAILURE);
	print_status(ph, EATING);
	precise_usleep(ph->table->time_to_eat);
	if (ph->table->meal_count > 0)
		if (set_meals_eaten(ph))
			return (EXIT_FAILURE);
	if (put_down_forks(ph))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}