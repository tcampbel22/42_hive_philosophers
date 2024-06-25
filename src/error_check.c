/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:49:39 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/25 10:54:49 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

int	check_numeric_arg(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (ft_is_num(av[i][j]))
				return (1);
		}
	}
	return (0);
}

void	ft_perror(char *str)
{
	int	i;

	i = -1;
	write(2, "philo: ", 8);
	while (str[++i])
		write(2, &str[i], 1);
}
