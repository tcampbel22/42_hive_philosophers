/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:49:39 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/03 10:20:08 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **av)
{
	int	i;

	i = 0;
	while (++i < 5)
	{
		if (ft_atol(av[i]) <= 0)
			return (ft_perror(ARG_ERR));
		else if (ft_atol(av[i]) > INT_MAX)
			return (ft_perror(ARG_SIZE_ERR));
	}
	if (av[5])
		if (atol(av[5]) < 0 || atol(av[5]) > INT_MAX)
			return (ft_perror(ARG_ERR));
	return (EXIT_SUCCESS);
}

int	ft_perror(char *str)
{
	write(2, "philo: ", 7);
	write(2, str, ft_strlen(str));
	return (EXIT_FAILURE);
}
