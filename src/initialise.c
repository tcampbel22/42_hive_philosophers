/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:55:30 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/01 16:26:09 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	assign_forks(t_philo *ph, t_fork *forks, int philo_pos)
{
	int	ph_num;

	ph_num = ph->table->ph_num;
	ph->left_fork = &forks[(philo_pos + 1) % ph_num];
	ph->right_fork = &forks[philo_pos];
	if (philo_pos % 2 == 0)
	{
		ph->right_fork = &forks[philo_pos];
		ph->left_fork = &forks[(philo_pos + 1) % ph_num];
	}
	return (EXIT_SUCCESS);	
}

static int	init_philo_struct(t_table *table, t_philo *ph, long ph_num)
{
	int	i;

	i = -1;
	while (++i < ph_num)
	{
		ph[i].id = i + 1;
		ph[i].full = false;
		ph[i].meals_eaten = 0;
		ph[i].table = table;
		assign_forks(&ph[i], table->forks, i);
	}
	return (EXIT_SUCCESS);
}

static int	init_mutex(t_table *table, long ph_num)
{
	int	i;

	i =  -1;
	while (++i < ph_num)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL))
			return (ft_perror(MTX_INIT_ERR));
		table->forks[i].fork_id = i;
	}
	i = -1;
	while (++i < ph_num)
		if (pthread_mutex_init(&table->ph[i].meals_eaten_lock, NULL))
			return (ft_perror(MTX_INIT_ERR));
	i = -1;
	while (++i < ph_num)
		if (pthread_mutex_init(&table->ph[i].last_meal_time_lock, NULL))
			return (ft_perror(MTX_INIT_ERR));		
	i =-1;
	while (++i < ph_num)
		if (pthread_mutex_init(&table->ph[i].full_lock, NULL))
			return (ft_perror(MTX_INIT_ERR));
	if (pthread_mutex_init(&table->dead_lock, NULL))
			return (ft_perror(MTX_INIT_ERR));
	return (EXIT_SUCCESS);

}
static int	init_table(t_table *table, char **av)
{
	table->ph = NULL;
	table->forks = NULL;
	table->end_dinner = false;
	table->ph_num = ft_atol(av[1]);
	if (table->ph_num > 1000)
		ft_perror("Not enough seats at the table :(\n");
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (av[5])
		table->meal_count = ft_atol(av[5]);
	else
		table->meal_count = -1;
	table->ph = malloc(sizeof(t_philo) * table->ph_num);
	table->forks = malloc(sizeof(t_fork) * table->ph_num);
	if (!table->ph || !table->forks)
		return(ft_perror(MALLOC_ERR));
	return (EXIT_SUCCESS);
}

int	init_structs(t_table *table, char **av)
{	
	if (init_table(table, av))
		return (EXIT_FAILURE);
	if (init_mutex(table, table->ph_num))
		return (EXIT_FAILURE);
	if (init_philo_struct(table, table->ph, table->ph_num))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}