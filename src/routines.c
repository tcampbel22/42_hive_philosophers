/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:39:18 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/03 19:13:31 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	forever_alone(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->left_fork->fork))
		return (ft_perror(MTX_LOCK_ERR));
	print_status(ph, L_FORK);
	precise_usleep(ph->table->time_to_die);
	print_status(ph, DEAD);
	if (pthread_mutex_lock(&ph->table->end_dinner_lock))
		return (ft_perror(MTX_LOCK_ERR));
	ph->table->end_dinner = true;
	if (pthread_mutex_unlock(&ph->table->end_dinner_lock))
		return (ft_perror(MTX_ULOCK_ERR));
	if (pthread_mutex_unlock(&ph->left_fork->fork))
		return (ft_perror(MTX_ULOCK_ERR));
	return (EXIT_FAILURE);
}

static void	ph_sleep(t_philo *ph)
{
	print_status(ph, SLEEPING);
	precise_usleep(ph->table->time_to_sleep);
}

static int	ph_think(t_philo *ph)
{
	print_status(ph, THINKING);
	if (pthread_mutex_lock(&ph->last_meal_time_lock))
		return (ft_perror(MTX_LOCK_ERR));
	precise_usleep((ph->table->time_to_die - \
			(get_time() - ph->last_meal_time) - ph->table->time_to_eat) / 2);
	if (pthread_mutex_unlock(&ph->last_meal_time_lock))
		return (ft_perror(MTX_ULOCK_ERR));
	return (EXIT_SUCCESS);
}

void	*dinner(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if (ph->table->ph_num == 0)
		forever_alone(ph);
	while (is_dead(ph->table) == 0)
	{
		if (ph->full == true)
			break ;
		ph_eat(ph);
		ph_sleep(ph);
		ph_think(ph);
	}
	return (NULL);
}
