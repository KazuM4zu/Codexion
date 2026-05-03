/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoyer <efoyer@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:45:28 by efoyer            #+#    #+#             */
/*   Updated: 2026/05/03 21:08:05 by efoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <time.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>

typedef struct s_node
{
	int			coder_id;
	long long	prio_val;
}	t_node;

typedef struct s_heap
{
	t_node	*nodes;
	int		size;
	int		capacity;
}	t_heap;

typedef struct s_dongle
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int is_taken;
    long long ready_at;
    t_heap wait_queue;
} t_dongle;

typedef struct s_coder
{
    int id;
    int compiles_done;
    int left_dongle;
    int right_dongle;
    long long last_compile_start;
    pthread_t thread;
    struct s_data *data;
} t_coder;

typedef struct s_data
{
    int number_of_coders;
    int nb_of_compiles_required;
    int scheduler;
    int stop_sim;
    long long time_to_burnout;
    long long time_to_compile;
    long long time_to_debug;
    long long time_to_refactor;
    long long dongle_cooldown;
    long long start_time;
    pthread_mutex_t log_lock;
    pthread_mutex_t stop_lock;
    t_dongle *dongles;
    t_coder *coders;
} t_data;


void		percolate_up(t_heap *heap, int i);
void		percolate_down(t_heap *heap, int i);
void		init_data(t_data *data, char **argv);
void		swap_nodes(t_node *a, t_node *b);
int         check_stop(t_data *data);
int         init_heap(t_heap *heap, t_data *data);
int			init_coders_dongers(t_data *data);
int			init_sync(t_data *data);
int			init_main(t_data *data, int argc, char **argv);
long long	get_time_in_ms(void);
long long   calculate_priority(t_coder *coder);
int         print_state(t_coder *coder, char *msg);
int			ft_isnumber(char *s);
int			check_global(int argc, char **argv);
void        *monitor_routine(void *arg);
void        *coder_routine(void *arg);
void        heap_push(t_heap *heap, int coder_id, long long priority);
    t_node heap_pop(t_heap *heap);

#endif