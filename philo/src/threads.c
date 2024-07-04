/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:32:02 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/04 16:41:20 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	thread_err(t_table *table, int index)
{
	if (index == -1)
		ft_perror(PTHREAD_CR_ERR);
	else if (index == -2)
		ft_perror(PTHREAD_JOIN_ERR);
	while (index-- > 0)
	{
		if (pthread_join(table->ph[index].thread, NULL))
			return (ft_perror(PTHREAD_JOIN_ERR));
	}
	if (destroy_mutexes(table, (int)table->ph_num, 1))
		return (EXIT_FAILURE);
	return (1);
}	

int	create_threads(t_table *table)
{
	int	i;

	i = -1;
	if (pthread_create(&table->waiter, NULL, &waiter_bot, table))
		return (thread_err(table, -1));
	while (++i < table->ph_num)
		if (pthread_create(&table->ph[i].thread, NULL, &dinner, &table->ph[i]))
			return (thread_err(table, i - 1));
	i = -1;
	while (++i < table->ph_num)
		if (pthread_join(table->ph[i].thread, NULL))
			return (thread_err(table, -2));
	if (pthread_join(table->waiter, NULL))
		return (thread_err(table, -2));
	if (destroy_mutexes(table, (int)table->ph_num, 1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	start_dinner(t_table *table)
{
	if (table->meal_count == 0)
		return (ft_perror(MEAL_COUNT_ERR));
	table->start_time = get_time();
	if (table->start_time == 1)
		return (EXIT_FAILURE);
	if (create_threads(table))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
