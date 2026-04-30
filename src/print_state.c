/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoyer <efoyer@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 11:11:44 by efoyer            #+#    #+#             */
/*   Updated: 2026/04/30 11:11:50 by efoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <sys/time.h>

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long) tv.tv_sec * 1000 + (long long) tv.tv_usec / 1000);
}

int	print_state(t_coder *coder, char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&coder->data->stop_lock);
	if (coder->data->stop_sim)
	{
		pthread_mutex_unlock(&coder->data->stop_lock);
		return (1);
	}
	pthread_mutex_unlock(&coder->data->stop_lock);
	timestamp = get_time_in_ms() - coder->data->start_time;
	pthread_mutex_lock(&coder->data->log_lock);
	printf("%lld %d %s\n", timestamp, coder->id, msg);
	pthread_mutex_unlock(&coder->data->log_lock);
}
