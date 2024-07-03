/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:49:50 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/03 19:07:29 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	check_philos(t_table *table)
{
	int		i;
	int		meals;

	i = -1;
	meals = 0;
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
		pthread_mutex_lock(&table->ph[i].meals_eaten_lock);
		meals += table->ph[i].meals_eaten;
		if (table->meal_count > 0 && meals == table->meal_count * table->ph_num)
			table->all_philos_full = true;
		pthread_mutex_unlock(&table->ph[i].meals_eaten_lock);
	}
}

void	*waiter(void *data)
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
