/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoyer <efoyer@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 19:24:48 by efoyer            #+#    #+#             */
/*   Updated: 2026/05/01 19:24:48 by efoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int is_burned_out(t_coder *coder)
{
	t_data *d = coder->data;
	int i;

	pthread_mutex_lock(&d->stop_lock);
	if (get_time_in_ms() - coder->last_compile_start > d->time_to_burnout)
	{
		d->stop_sim = 1;
		pthread_mutex_unlock(&d->stop_lock);
		print_state(coder, "burned out");
		i = -1;
		while (++i < d->number_of_coders)
		{
			pthread_mutex_lock(&d->dongles[i].mutex);
			pthread_cond_broadcast(&d->dongles[i].cond);
			pthread_mutex_unlock(&d->dongles[i].mutex);
		}
		return (1);
	}
	pthread_mutex_unlock(&d->stop_lock);
	return (0);
}

static int check_all_full(t_data *data)
{
	int i;
	int finished;

	i = 0;
	finished = 0;
	while (i < data->number_of_coders)
	{
		pthread_mutex_lock(&data->stop_lock);
		if (data->coders[i].compiles_done >= data->nb_of_compiles_required)
			finished++;
		pthread_mutex_unlock(&data->stop_lock);
		i++;
	}
	return (finished == data->number_of_coders);
}

void *monitor_routine(void *arg)
{
	t_data *data;
	int i;

	data = (t_data *)arg;
	while (!check_stop(data))
		{
			if (check_all_full(data))
				{
					pthread_mutex_lock(&data->stop_lock);
					data->stop_sim = 1;
					pthread_mutex_unlock(&data->stop_lock);
					return (NULL);
				} i = 0;
			while (i < data->number_of_coders)
			{
				if (is_burned_out(&data->coders[i]))
					return (NULL);
				i++;
			}
			usleep(1000);
		} return (NULL);
}