/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoyer <efoyer@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:45:33 by efoyer            #+#    #+#             */
/*   Updated: 2026/05/01 20:02:50 by efoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	cleanup_and_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_coders)
	{
		pthread_mutex_destroy(&data->dongles[i].mutex);
		pthread_cond_destroy(&data->dongles[i].cond);
		free(data->dongles[i].wait_queue.nodes);
		i++;
	}
	pthread_mutex_destroy(&data->log_lock);
	pthread_mutex_destroy(&data->stop_lock);
	free(data->coders);
	free(data->dongles);
}

int main(int argc, char **argv)
{
	t_data  	data;
	pthread_t	monitor;
    int 		i;

	if (init_main(&data, argc, argv) != 0 || init_sync(&data) != 0)
		return (1);
	data.start_time = get_time_in_ms();
	i = -1;
	while (++i < data.number_of_coders)
		pthread_create(&data.coders[i].thread, NULL, &coder_routine, &data.coders[i]);
	pthread_create(&monitor, NULL, &monitor_routine, &data);
	i = -1;
	while (++i < data.number_of_coders)
		pthread_join(data.coders[i].thread, NULL);
	pthread_join(monitor, NULL);
	cleanup_and_exit(&data);
	return (0);
}
