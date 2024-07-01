/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:07:58 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/01 16:42:14 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ft_perror(TIME_ERR));
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));	
}

void	precise_usleep(long time)
{
	long	stop;

	stop = get_time() + time;
	while (get_time() < stop)
		usleep(100);
}