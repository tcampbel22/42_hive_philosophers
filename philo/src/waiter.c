/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:49:50 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/05 13:50:13 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

void	check_philos(t_table *table, int meals)
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
		pthread_mutex_lock(&table->ph[i].full_lock);
		if (table->ph[i].full == true)
			meals++;
		pthread_mutex_lock(&table->end_dinner_lock);
		if (table->meal_count > 0 && meals == table->ph_num)
			table->end_dinner = true;
		pthread_mutex_unlock(&table->ph[i].full_lock);
		pthread_mutex_unlock(&table->end_dinner_lock);
	}
}

void	*waiter_bot(void *data)
{
	t_table	*table;
	int		meals;

	meals = 0;
	table = (t_table *)data;
	while (1)
	{	
		check_philos(table, meals);
		if (is_dead(table))
			break ;
	}
	return (NULL);
}
