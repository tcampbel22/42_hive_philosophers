/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:55:30 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/26 15:02:27 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i =  -1;
	 data->forks= malloc(sizeof(pthread_mutex_t) * (data->ph->ph_num + 1));
	if (!data->forks)
		return (ft_perror("malloc failure\n"));
	while (++i < data->ph->ph_num)
		pthread_mutex_init(&data->forks[i], NULL);
	return (0);

}
int	init_data_struct(t_data *data, char **av)
{
	int		philo_count;

	philo_count = ft_atoi(av[1]);
	data->ph = malloc(sizeof(t_philo) * (philo_count + 1));
	if (!data->ph)
		return(ft_perror("malloc failure"));
	init_philo_struct(av, data->ph);
	init_mutex(data);
	return (0);
}

int	init_philo_struct(char **av, t_philo *ph)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		ph[i].id = i + 1;
		ph[i].x_eat = 0;
		ph[i].ph_num = ft_atoi(av[1]);
		ph[i].time_to_die = ft_atoi(av[2]);
		ph[i].time_to_eat = ft_atoi(av[3]);
		ph[i].time_to_sleep = ft_atoi(av[4]);
		if (av[5] != NULL)
			ph[i].x_eat = ft_atoi(av[5]);
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