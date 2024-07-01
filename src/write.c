/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:42:28 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/01 17:01:03 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_status(t_philo *ph, t_ph_status status)
{
	long	time;

	time = get_time() - ph->table->start_time;	
	if (ph->full == true)
		return (EXIT_SUCCESS);
	if (pthread_mutex_lock(&ph->table->dead_lock))
		return (ft_perror(MTX_LOCK_ERR));
	if (ph->table->end_dinner == false)
	{
		if (status == L_FORK)
			printf("%ld : %ld picked up their left fork\n", time, ph->id);
		else if (status == R_FORK)
			printf("%ld : %ld picked up their right fork\n", time, ph->id);
		else if (status == EATING)
			printf("%ld : %ld is eating\n", time, ph->id);
		else if (status == THINKING)
			printf("%ld : %ld is thinking\n", time, ph->id);
		else if (status == SLEEPING)
			printf("%ld : %ld is sleeping\n", time, ph->id);
		else if (status == DEAD)
			printf("%ld : %ld is dead\n", time, ph->id);
	}
	if (pthread_mutex_unlock(&ph->table->dead_lock))
		return (ft_perror(MTX_ULOCK_ERR));
	return (EXIT_SUCCESS);
}