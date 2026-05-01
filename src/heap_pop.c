/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoyer <efoyer@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 12:35:03 by efoyer            #+#    #+#             */
/*   Updated: 2026/05/01 18:50:45 by efoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	is_higher_priority(t_node a, t_node b)
{
	if (a.prio_val < b.prio_val)
		return (1);
	if (a.prio_val == b.prio_val && a.coder_id < b.coder_id)
		return (1);
	return (0);
}

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
		if (left < heap->size && is_higher_priority(heap->nodes[left], \
			heap->nodes[smallest]))
			smallest = left;
		if (right < heap->size && is_higher_priority(heap->nodes[right], \
			heap->nodes[smallest]))
			smallest = right;
		if (smallest == i)
			break ;
		swap_nodes(&heap->nodes[i], &heap->nodes[smallest]);
		i = smallest;
	}
}

t_node	heap_pop(t_heap *heap)
{
	t_node	root;

	if (heap->size <= 0)
		return ((t_node){0, 0});
	root = heap->nodes[0];
	heap->nodes[0] = heap->nodes[heap->size - 1];
	heap->size--;
	if (heap->size > 0)
		percolate_down(heap, 0);
	return (root);
}
