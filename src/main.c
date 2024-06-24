/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:38:32 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/24 15:53:29 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_stuct(char **av)
{
    t_philo ph;

    ph = malloc(sizeof(t_philo *));
    if (!ph)
        return (1);
    ph->philo_num = ft_atoi(av[0]);
    ph->time_to_die = ft_atoi(av[1]);
    ph->time_to_eat = ft_atoi(av[2]);
    ph->time_to_sleep = ft_atoi(av[3]);
    ph->x_eat = ft_atoi(av[4]);
    return (0);
}

int main(int ac, char **av)
{
    if (ac != 4)
        return (1);
    if (init_stuct(av) == 1)
    {
        printf("Malloc failure\n");
        return (1);
    }
}