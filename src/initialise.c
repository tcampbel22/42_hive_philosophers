/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:55:30 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/27 16:30:14 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *waiter)
{
	int	i;

	i =  -1;
	waiter->fork = malloc(sizeof(t_fork));
	if (!waiter->fork)
		return (ft_perror("malloc failure\n"));
	waiter->fork->forks= malloc(sizeof(pthread_mutex_t) * (waiter->ph_num + 1));
	if (!waiter->fork->forks)
		return (ft_perror("malloc failure\n"));
	while (++i < waiter->ph_num)
		pthread_mutex_init(&waiter->fork->forks[i], NULL);
	return (0);

}
int	init_data_struct(t_data *waiter, char **av)
{	
	waiter->ph_num = ft_atol(av[1]);
	if (waiter->ph_num > 1000)
		ft_perror("Not enough seats at the table :(\n");
	waiter->time_to_die = ft_atol(av[2]);
	waiter->time_to_eat = ft_atol(av[3]);
	waiter->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		waiter->meal_count = ft_atol(av[5]);
	else
		waiter->meal_count = -1;
	if (init_philo_struct(av, waiter->ph, waiter->ph_num))
		return (1);
	if (init_mutex(waiter))
		return (1);
	return (0);
}

int	init_philo_struct(char **av, t_philo *ph, long ph_num)
{
	int	i;

	i = -1;
	ph = malloc(sizeof(t_philo) * (ph_num + 1));
	if (!ph)
		return(ft_perror("malloc failure"));
	while (++i < ft_atol(av[1]))
	{
		ph[i].id = i + 1;
		ph->thread = create_thread(ph->thread);
		if (ph->thread == 1)
			return (1);	
		//printf("ph_num = %ld\ntime_to_die = %ld\ntime_to_eat = %ld\ntime_to_sleep = %ld\nx_eat = %ld\n", ph[i].ph_num, ph[i].time_to_die, ph[i].time_to_eat, ph[i].time_to_sleep, ph[i].x_eat);
	}
	return (0);
}
void	*routine()
{
	int	test;

	test = 0;
	while (test < 20)
		test++;
	printf("%d\n", test);
	return (NULL);
}

pthread_t	create_thread(pthread_t thread)
{
	if (pthread_create(&thread, NULL, &routine, NULL))
		return(ft_perror("failed to create thread\n"));
	if (pthread_join(thread, NULL))
		return(ft_perror("thread failed to join"));
	return (thread);
}