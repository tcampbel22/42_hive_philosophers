/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:28:40 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/05 13:50:25 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	destroy_forks(t_table *table, int index)
{
	int	flag;

	flag = 0;
	while (index-- > 0)
		if (pthread_mutex_destroy(&table->forks[index].fork))
			flag = 1;
	if (flag)
		return (ft_perror(MTX_DES_ERR));
	return (0);
}

int	destroy_meals(t_table *table, int index)
{
	int	flag;

	flag = 0;
	destroy_forks(table, index);
	while (index-- > 0)
		if (pthread_mutex_destroy(&table->ph[index].meals_eaten_lock))
			flag = 1;
	if (flag)
		return (ft_perror(MTX_DES_ERR));
	return (0);
}

int	destroy_time_lock(t_table *table, int index)
{
	int	flag;

	flag = 0;
	destroy_meals(table, index);
	while (index-- > 0)
		if (pthread_mutex_destroy(&table->ph[index].last_meal_time_lock))
			flag = 1;
	if (flag)
		return (ft_perror(MTX_DES_ERR));
	return (0);
}

int	destroy_full_lock(t_table *table, int index)
{
	int	flag;

	flag = 0;
	destroy_time_lock(table, index);
	while (index-- > 0)
		if (pthread_mutex_destroy(&table->ph[index].full_lock))
			flag = 1;
	if (flag)
		return (ft_perror(MTX_DES_ERR));
	return (0);
}

int	destroy_mutexes(t_table *table, int index, int flag)
{
	int	i;

	i = 0;
	i = destroy_full_lock(table, index);
	if (flag)
		if (pthread_mutex_destroy(&table->end_dinner_lock))
			i++;
	return (i);
}
