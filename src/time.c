/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:07:58 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/28 16:46:36 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


size_t	get_time(t_table *table)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ft_perror("failed to get time\n"));
	table->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (EXIT_SUCCESS);	
}