/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:49:39 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/28 15:19:18 by tcampbel         ###   ########.fr       */
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
			return (ft_perror("invalid arg\n"));
		else if (ft_atol(av[i]) > INT_MAX)
			return (ft_perror("int max exceeded\n"));
	}
	if (av[5])
		if (atol(av[5]) < 0 || atol(av[5]) > INT_MAX)
			return (ft_perror("invalid arg\n"));
	return (0);
}

int	ft_perror(char *str)
{
	int	i;

	i = -1;
	write(2, "philo: ", 8);
	while (str[++i])
		write(2, &str[i], 1);
	return (1);
}
