/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoyer <efoyer@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 18:53:22 by efoyer            #+#    #+#             */
/*   Updated: 2026/05/01 18:53:22 by efoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	release_dongle(t_coder *coder, int d_id)
{
	t_dongle	*d;

	d = &coder->data->dongles[d_id];
	pthread_mutex_lock(&d->mutex);
	d->is_taken = 0;
	d->ready_at = get_time_in_ms() + coder->data->dongle_cooldown;
	pthread_cond_broadcast(&d->cond);
	pthread_mutex_unlock(&d->mutex);
}

void acquire_dongle(t_coder *coder, int d_id)
{
	t_dongle *d;
	long long wait_time;

	d = &coder->data->dongles[d_id];
	pthread_mutex_lock(&d->mutex);
	heap_push(&d->wait_queue, coder->id, calculate_priority(coder));
	while (d->wait_queue.nodes[0].coder_id != coder->id || d->is_taken)
	{
		if (check_stop(coder->data))
			return ((void)pthread_mutex_unlock(&d->mutex));
		pthread_cond_wait(&d->cond, &d->mutex);
	}
	wait_time = d->ready_at - get_time_in_ms();
	if (wait_time > 0)
		usleep(wait_time * 1000);
	d->is_taken = 1;
	heap_pop(&d->wait_queue);
	pthread_mutex_unlock(&d->mutex);
	print_state(coder, "has taken a dongle");
}

static void	execute_work(t_coder *coder)
{
	print_state(coder, "is compiling");
	pthread_mutex_lock(&coder->data->stop_lock);
	coder->last_compile_start = get_time_in_ms();
	coder->compiles_done++;
	pthread_mutex_unlock(&coder->data->stop_lock);
	usleep(coder->data->time_to_compile * 1000);
	release_dongle(coder, coder->left_dongle);
	release_dongle(coder, coder->right_dongle);
}

void	*coder_routine(void *arg)
{
	t_coder	*c;
	int		low;
	int		high;

	c = (t_coder *)arg;
	low = c->left_dongle;
	high = c->right_dongle;
	if (low > high)
	{
		low = c->right_dongle;
		high = c->left_dongle;
	}
	while (!check_stop(c->data))
	{
		acquire_dongle(c, low);
		acquire_dongle(c, high);
		execute_work(c);
		print_state(c, "is debugging");
		usleep(c->data->time_to_debug * 1000);
		print_state(c, "is refactoring");
		usleep(c->data->time_to_refactor * 1000);
	}
	return (NULL);
}