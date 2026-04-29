/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoyer <efoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:54:01 by efoyer            #+#    #+#             */
/*   Updated: 2026/04/29 13:37:37 by efoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "codexion.h"

void    init_data(t_data *data, char **argv)
{
    data->number_of_coders = atoi(argv[1]);
    data->time_to_burnout = atoi(argv[2]);
    data->time_to_compile = atoi(argv[3]);
    data->time_to_debug = atoi(argv[4]);
    data->time_to_refactor = atoi(argv[5]);
    data->nb_of_compiles_required = atoi(argv[6]);
    data->dongle_cooldown = atoi(argv[7]);
    data->scheduler = atoi(argv[8]);
}


int init_main(t_data *data, int argc, char **argv)
{
    if (check_global(argc, argv) != 0)
    {
        printf("Error\n");
        return (1);
    }
    init_data(data, argv);
}