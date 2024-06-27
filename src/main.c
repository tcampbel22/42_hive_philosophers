/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:38:32 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/27 14:30:34 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_data *waiter)
{
	if (waiter->ph)
		free(waiter->ph);
	if (waiter->fork->forks)
		free(waiter->fork->forks);
	if (waiter->fork)
		free(waiter->fork);
	if (waiter)
		free(waiter);
}

int	main(int ac, char **av)
{
	t_data	*waiter;

	if (ac != 5 && ac !=  6)
		return (ft_perror("invalid arg amount\n"));
	if (check_args(av))
		return (1);
	waiter = malloc(sizeof(t_data));
	if (!waiter)
		return (ft_perror("malloc failure\n"));
	if (init_data_struct(waiter, av))
	{
		//free_all(waiter);
		return (1);
	}
	free_all(waiter);
	return (0);
}

