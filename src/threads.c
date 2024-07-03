/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:32:02 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/03 15:40:16 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_table *table)
{
	int	i;

	i = -1;
	if (pthread_create(&table->waiter, NULL, &waiter, table))
		return (ft_perror(PTHREAD_CR_ERR));
	while (++i < table->ph_num)
		if (pthread_create(&table->ph[i].thread, NULL, &dinner, &table->ph[i]))
			return (ft_perror(PTHREAD_CR_ERR));
	i = -1;
	while (++i < table->ph_num)
		if (pthread_join(table->ph[i].thread, NULL))
			return (ft_perror(PTHREAD_JOIN_ERR));
	if (pthread_join(table->waiter, NULL))
		return (ft_perror(PTHREAD_JOIN_ERR));
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
