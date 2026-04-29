/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoyer <efoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:45:28 by efoyer            #+#    #+#             */
/*   Updated: 2026/04/29 13:43:37 by efoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <unistd.h>
# include <limits.h>

typedef struct  s_dongle
{
    int id;
    int *waiting_ids;
    int wait_count;
}   t_dongle;


typedef struct s_data
{
    int number_of_coders;
    int nb_of_compiles_required;
    int scheduler;
    int stop_sim;
    long long time_to_burnout;
    long long time_to_compile;
    long long time_to_debug;
    long long time_to_refactor;
    long long dongle_cooldown;
    long long start_time;
    
}   t_data;

void    init_data(t_data *data, char **argv);
int init_main(t_data *data, int argc, char **argv);
int ft_isnumber(char *s);
int check_global(int argc, char **argv);

#endif