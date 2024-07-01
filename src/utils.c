/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:03:40 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/28 16:00:50 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	convert_char(const char *str)
{
	long	num;

	num = 0;
	while (*str >= 48 && *str <= 57)
	{
		num = (num * 10) + (*str - 48);
		str++;
	}
	return (num);
}

long	ft_atol(const char *str)
{
	int		neg;
	long	num;

	neg = 1;
	num = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	num = convert_char(str);
	return (num * neg);
}

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}
