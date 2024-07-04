/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:42:28 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/04 15:09:07 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	print_status(t_philo *ph, t_ph_status status)
{
	long	time;

	time = get_time() - ph->table->start_time;
	if (is_full(ph) == 0)
		return (EXIT_SUCCESS);
	pthread_mutex_lock(&ph->table->end_dinner_lock);
	if (ph->table->end_dinner == false)
	{
		if (status == L_FORK)
			printf(C"%ld"G" [%ld]"W" has taken a left fork\n"E, time, ph->id);
		else if (status == R_FORK)
			printf(C"%ld"G" [%ld]"W" has taken a right fork\n"E, time, ph->id);
		else if (status == EATING)
			printf(C"%ld"G" [%ld]"B" is eating\n"E, time, ph->id);
		else if (status == THINKING)
			printf(C"%ld"G" [%ld]"M" is thinking\n"E, time, ph->id);
		else if (status == SLEEPING)
			printf(C"%ld"G" [%ld]"Y" is sleeping\n"E, time, ph->id);
		else if (status == DEAD)
			printf(C"%ld"G" [%ld]"RD" is dead\n"E, time, ph->id);
	}
	pthread_mutex_unlock(&ph->table->end_dinner_lock);
	return (EXIT_SUCCESS);
}
