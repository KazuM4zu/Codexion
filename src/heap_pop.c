/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoyer <efoyer@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 12:35:03 by efoyer            #+#    #+#             */
/*   Updated: 2026/04/30 12:35:05 by efoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	percolate_down(t_heap *heap, int i)
{
	int	left;
	int	right;
	int	smallest;

	while (1)
	{
		left = 2 * i + 1;
		right = 2 * i + 2;
		smallest = i;
		if (left < heap->size && (heap->nodes[left].prio_val < \
			heap->nodes[smallest].prio_val || (heap->nodes[left].prio_val == \
			heap->nodes[smallest].prio_val && heap->nodes[left].coder_id < \
			heap->nodes[smallest].coder_id)))
			smallest = left;
		if (right < heap->size && (heap->nodes[right].prio_val < \
			heap->nodes[smallest].prio_val || (heap->nodes[right].prio_val == \
			heap->nodes[smallest].prio_val && heap->nodes[right].coder_id < \
			heap->nodes[smallest].coder_id)))
			smallest = right;
		if (smallest != i)
		{
			swap_nodes(&heap->nodes[i], &heap->nodes[smallest]);
			i = smallest;
		}
		else
			break ;
	}
}
