/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:38:32 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/03 10:15:14 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	destroy_mutexes(t_table *table)
{
	int	i;

	i =  -1;
	while (++i < table->ph_num)
	{
		if (pthread_mutex_destroy(&table->forks[i].fork))
			return (ft_perror(MTX_DESTROY_ERR));
		if (pthread_mutex_destroy(&table->ph[i].full_lock))
			return (ft_perror(MTX_DESTROY_ERR));
		if (pthread_mutex_destroy(&table->ph[i].last_meal_time_lock))
			return (ft_perror(MTX_DESTROY_ERR));
		if (pthread_mutex_destroy(&table->ph[i].meals_eaten_lock))
			return (ft_perror(MTX_DESTROY_ERR));
	}
	if (pthread_mutex_destroy(&table->end_dinner_lock))
		return (ft_perror(MTX_INIT_ERR));
	if (pthread_mutex_destroy(&table->ph_wait_lock))
		return (ft_perror(MTX_INIT_ERR));
	return (EXIT_SUCCESS);
}

int	free_all(t_table *table, int status)
{
	if (destroy_mutexes(table))
		return (EXIT_FAILURE);
	if (table->ph)
		free(table->ph);
	if (table->forks)
		free(table->forks);
	return (status);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (ft_perror("Invalid arg amount\n"));
	if (check_args(av))
		return (EXIT_FAILURE);
	if (init_structs(&table, av))
		return (free_all(&table, EXIT_FAILURE));
	if (start_dinner(&table))
		return (free_all(&table, EXIT_FAILURE));
	return(free_all(&table, EXIT_SUCCESS));
}

