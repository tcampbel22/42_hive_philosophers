/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:39:18 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/05 13:49:56 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	forever_alone(t_philo *ph)
{
	pthread_mutex_lock(&ph->left_fork->fork);
	print_status(ph, L_FORK);
	precise_usleep(ph->table->time_to_die);
	print_status(ph, DEAD);
	pthread_mutex_lock(&ph->table->end_dinner_lock);
	ph->table->end_dinner = true;
	pthread_mutex_unlock(&ph->table->end_dinner_lock);
	pthread_mutex_unlock(&ph->left_fork->fork);
	return (EXIT_SUCCESS);
}

static void	ph_sleep_and_think(t_philo *ph)
{
	print_status(ph, SLEEPING);
	precise_usleep(ph->table->time_to_sleep);
	print_status(ph, THINKING);
}

void	*dinner(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if (ph->table->ph_num == 1)
		forever_alone(ph);
	if (ph->id % 2)
		precise_usleep(ph->table->time_to_eat);
	while (is_dead(ph->table) == 0)
	{
		ph_eat(ph);
		ph_sleep_and_think(ph);
	}
	return (NULL);
}
