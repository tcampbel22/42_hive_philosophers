/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:38:32 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/26 15:02:39 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data data;

	if (ac != 5 && ac !=  6)
		return (ft_perror("invalid arg amount\n"));
	if (check_args(av))
		return (ft_perror("invalid arg\n"));
	if (init_data_struct(&data, av))
		return (1);
	free(data.ph);
	free(data.forks);
	return (0);
}

