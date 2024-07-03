/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:32:02 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/03 10:59:26 by tcampbel         ###   ########.fr       */
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
	precise_usleep((ph->table->time_to_die - (get_time() - ph->last_meal_time) - ph->table->time_to_eat) / 2);
	if (pthread_mutex_unlock(&ph->last_meal_time_lock))
		return (ft_perror(MTX_ULOCK_ERR));
	return (EXIT_SUCCESS);
}

void	*dinner(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if (ph->table->ph_num == 1)
		forever_alone(ph);
	pthread_mutex_lock(&ph->table->ph_wait_lock);
	ph->table->ph_wait++;
	pthread_mutex_unlock(&ph->table->ph_wait_lock);
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

int	create_threads(t_table *table)
{
	int	i;

	i = -1;
	if (pthread_create(&table->waiter, NULL, &waiter, table))
		return (ft_perror(PTHREAD_CR_ERR));
	while (++i < table->ph_num)
		if (pthread_create(&table->ph[i].thread, NULL, &dinner, &table->ph[i]))
			return(ft_perror(PTHREAD_CR_ERR));
	i = -1;
	while (++i < table->ph_num)
		if (pthread_join(table->ph[i].thread, NULL))
			return(ft_perror(PTHREAD_JOIN_ERR));
	if (pthread_join(table->waiter, NULL))
		return (ft_perror(PTHREAD_JOIN_ERR));
	return (EXIT_SUCCESS);
}

int	start_dinner(t_table *table)
{
	if (table->meal_count == 0)
		return (ft_perror(MEAL_COUNT_ERR));
	table->start_time = get_time();
	if(table->start_time == 1)
		return (EXIT_FAILURE);
	if (create_threads(table))
		return (EXIT_FAILURE);
	return(EXIT_SUCCESS);
}
