/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:32:02 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/28 16:49:37 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner(void *philo)
{
	t_philo	*ph;

	ph = philo;
	usleep(5000);
	printf("philo[%ld] is eating\n", ph->id);
	return (NULL);
}

int	create_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->ph_num)
		if (pthread_create(&table->ph[i].thread, NULL, &dinner, &table->ph[i]))
			return(ft_perror("failed to create thread\n"));
	if (get_time(table))
		return (EXIT_FAILURE);
	i = -1;
	while (++i < table->ph_num)
		if (pthread_join(table->ph[i].thread, NULL))
			return(ft_perror("thread failed to join"));
	printf("time in millisecond: %zu\n", table->start_time);
	return (EXIT_SUCCESS);
}

int	start_dinner(t_table *table)
{
	if (table->meal_count == 0)
		return (ft_perror("meal count is zero, booooooooo!"));
	if (table->ph_num == 1)
		return (ft_perror("philo died\n")); //TODO 
	if (create_threads(table))
		return (EXIT_FAILURE);
	if (pthread_create(&table->waiter, NULL, &dinner, NULL))
		return (ft_perror("failed to create thread"));
	return(EXIT_SUCCESS);
}
