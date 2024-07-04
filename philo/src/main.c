/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:38:32 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/04 14:58:40 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	free_all(t_table *table, int status)
{
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
		return (ft_perror(ARG_COUNT_ERR));
	if (check_args(av))
		return (EXIT_FAILURE);
	if (init_structs(&table, av))
		return (free_all(&table, EXIT_FAILURE));
	if (start_dinner(&table))
		return (free_all(&table, EXIT_FAILURE));
	return (free_all(&table, EXIT_SUCCESS));
}
