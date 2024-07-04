/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:49:50 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/04 15:25:39 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_full(t_philo *ph)
{
	pthread_mutex_lock(&ph->full_lock);
	if (ph->full == true)
	{
		pthread_mutex_unlock(&ph->full_lock);
		return (EXIT_SUCCESS);
	}
	pthread_mutex_unlock(&ph->full_lock);
	return (1);
}

int	is_dead(t_table *table)
{
	pthread_mutex_lock(&table->end_dinner_lock);
	if (table->end_dinner == true)
	{
		pthread_mutex_unlock(&table->end_dinner_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->end_dinner_lock);
	return (0);
}

static void	is_all_philos_full(t_table *table, int i)
{
	int	meals;

	meals = 0;
	pthread_mutex_lock(&table->ph[i].full_lock);
	if (table->ph[i].full == true)
		meals++;
	if (table->meal_count > 0 && meals == table->ph_num)
		table->all_philos_full = true;
	pthread_mutex_unlock(&table->ph[i].full_lock);
}

void	check_philos(t_table *table)
{
	int		i;

	i = -1;
	while (++i < table->ph_num)
	{
		pthread_mutex_lock(&table->ph[i].last_meal_time_lock);
		if ((get_time() - table->start_time - table->ph[i].last_meal_time) \
					>= table->time_to_die && is_dead(table) == 0)
		{
			print_status(&table->ph[i], DEAD);
			pthread_mutex_lock(&table->end_dinner_lock);
			table->end_dinner = true;
			pthread_mutex_unlock(&table->end_dinner_lock);
		}
		pthread_mutex_unlock(&table->ph[i].last_meal_time_lock);
		is_all_philos_full(table, i);
	}
}

void	*waiter_bot(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	while (1)
	{
		check_philos(table);
		if (table->all_philos_full == true)
			break ;
		if (is_dead(table))
			break ;
	}
	return (NULL);
}
