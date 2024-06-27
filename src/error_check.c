/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:49:39 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/27 13:56:08 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(const char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (0);
	return (1);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

int	check_args(char **av)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			while (!ft_isspace(av[i][j]))
				++j;
			if (av[i][j] == '+')
				++j;
			else if (ft_is_num(av[i][j]))
				return (ft_perror("invalid arg\n"));
			k = j;
			while (!ft_is_num(av[i][k]))
				++k;
			if (ft_strlen(av[i]) - j > 10 || ft_atol(av[i]) > INT_MAX)
				return (ft_perror("exceeded MAX_INT\n"));
		}
	}
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
