/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoyer <efoyer@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 11:35:17 by efoyer            #+#    #+#             */
/*   Updated: 2026/05/01 19:46:42 by efoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_heap(t_heap *heap, t_data *data)
{
	heap->capacity = data->number_of_coders;
	heap->size = 0;
	heap->nodes = malloc(sizeof(t_node) * heap->capacity);
	if (!heap->nodes)
		return (1);
	return (0);
}

void	percolate_up(t_heap *heap, int i)
{
	int	parent;

	while (i > 0)
	{
		parent = (i - 1) / 2;

		if (heap->nodes[i].prio_val < heap->nodes[parent].prio_val)
			swap_nodes(&heap->nodes[i], &heap->nodes[parent]);

		else if (heap->nodes[i].prio_val == heap->nodes[parent].prio_val \
				&& heap->nodes[i].coder_id < heap->nodes[parent].coder_id)
			swap_nodes(&heap->nodes[i], &heap->nodes[parent]);
		else
			break ;
		i = parent;
	}
}

void	heap_push(t_heap *heap, int coder_id, long long priority)
{
	int		i;
	t_node	new_node;

	new_node.coder_id = coder_id;
	new_node.prio_val = priority;
	i = heap->size;
	heap->nodes[i] = new_node;
	heap->size++;
	percolate_up(heap, i);
}
