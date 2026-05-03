/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoyer <efoyer@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:54:01 by efoyer            #+#    #+#             */
/*   Updated: 2026/05/03 21:08:22 by efoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	init_data(t_data *data, char **argv)
{
	data->number_of_coders = atoi(argv[1]);
	data->time_to_burnout = atoi(argv[2]);
	data->time_to_compile = atoi(argv[3]);
	data->time_to_debug = atoi(argv[4]);
	data->time_to_refactor = atoi(argv[5]);
	data->nb_of_compiles_required = atoi(argv[6]);
	data->dongle_cooldown = atoi(argv[7]);
	if (strcmp(argv[8], "fifo") == 0)
		data->scheduler = 0;
	else if (strcmp(argv[8], "edf") == 0)
		data->scheduler = 1;
}

int	init_coders_dongers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_coders)
	{
		data->dongles[i].is_taken = 0;
		data->dongles[i].ready_at = 0;
		pthread_mutex_init(&data->dongles[i].mutex, NULL);
		pthread_cond_init(&data->dongles[i].cond, NULL);
		data->coders[i].id = i + 1;
		data->coders[i].compiles_done = 0;
		data->coders[i].data = data;
		data->coders[i].left_dongle = i;
		data->coders[i].right_dongle = (i + 1) % data->number_of_coders;
        data->coders[i].last_compile_start = get_time_in_ms();
        init_heap(&(data->dongles[i].wait_queue), data);
		i++;
	}
	return (0);
}

int	init_sync(t_data *data)
{
	data->coders = malloc(sizeof(t_coder) * data->number_of_coders);
	data->dongles = malloc(sizeof(t_dongle) * data->number_of_coders);
	if (!data->coders || !data->dongles)
		return (1);
	pthread_mutex_init(&data->log_lock, NULL);
	pthread_mutex_init(&data->stop_lock, NULL);
	init_coders_dongers(data);
    return (0);
}

int	init_main(t_data *data, int argc, char **argv)
{
	if (check_global(argc, argv) != 0)
	{
		printf("Error\n");
		return (1);
	}
	init_data(data, argv);
	return (0);
}