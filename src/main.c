/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:38:32 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/25 11:24:57 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	init_stuct(char **av, t_philo ph)
{
	ph.ph_num = ft_atoi(av[1]);
	ph.time_to_die = ft_atoi(av[2]);
	ph.time_to_eat = ft_atoi(av[3]);
	ph.time_to_sleep = ft_atoi(av[4]);
	ph.x_eat = ft_atoi(av[5]);
	return (ph);
}

void	*test_function()
{
	int	test;

	test = 0;
	while (test < 20)
		test++;
	printf("%d\n", test);
	return (NULL);
}

int	create_threads(t_philo *ph)
{
	pthread_t	*thread;
	int			i;

	thread = malloc(sizeof(pthread_t) * ph->ph_num);
	if (!thread)
	{
		ft_perror("malloc failure\n");
		return (1);
	}
	i = -1;
	while (++i < ph->ph_num)
		if (pthread_create(&thread[i], NULL, &test_function, NULL))
			return (1);
	i = -1;
	while (++i < ph->ph_num)
		if (pthread_join(thread[i], NULL))
			return (2);
	free(thread);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	ph;

	if (ac != 6)
	{
		ft_perror("invalid arg amount\n");
		return (1);
	}
	if (check_numeric_arg(av))
	{
		ft_perror("non-numeric arg\n");
		return (1);
	}
	ph = init_stuct(av, ph);
	create_threads(&ph);
	printf("ph_num = %d\ntime_to_die = %d\ntime_to_eat = %d\ntime_to_sleep = %d\nx_eat = %d\n", ph.ph_num, ph.time_to_die, ph.time_to_eat, ph.time_to_sleep, ph.x_eat);
	return (0);
}
