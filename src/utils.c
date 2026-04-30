/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoyer <efoyer@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 12:27:48 by efoyer            #+#    #+#             */
/*   Updated: 2026/04/30 12:27:53 by efoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	swap_nodes(t_node *a, t_node *b)
{
	t_node	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

long long	calculate_priority(t_coder *coder)
{
	t_data		*data;
	long long	priority;

	data = coder->data;
	pthread_mutex_lock(&data->stop_lock);

	if (data->scheduler == 0)
		priority = get_time_in_ms();
	else
		priority = coder->last_compile_start + data->time_to_burnout;
	pthread_mutex_unlock(&data->stop_lock);
	return (priority);
}
