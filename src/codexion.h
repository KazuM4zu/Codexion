/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoyer <efoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:45:28 by efoyer            #+#    #+#             */
/*   Updated: 2026/04/29 13:43:37 by efoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_coder
{
	int				id;
	int				compiles_done;
	int				left_dongle;
	int				right_dongle;
	long long		last_compile_start;
	pthread_t		thread;
	struct s_data	*data;	
}	t_coder;

typedef struct s_dongle
{
	pthread_mutex_t	mutex; // Protège l'accès au dongle
	pthread_cond_t	cond; // Pour mettre les codeurs en attente
	int				is_taken; // État actuel
	long long		ready_at; // Timestamp pour le cooldown
	// Ton Heap (file de priorité) ira ici pour l'arbitrage
}	t_dongle;

typedef struct s_data
{
	int				number_of_coders;
	int				nb_of_compiles_required;
	int				scheduler;
	int				stop_sim;
	long long		time_to_burnout;
	long long		time_to_compile;
	long long		time_to_debug;
	long long		time_to_refactor;
	long long		dongle_cooldown;
	long long		start_time;
	pthread_mutex_t	log_lock;
	pthread_mutex_t	stop_lock;
	t_dongle		*dongles;
	t_coder			*coders;
}	t_data;

typedef struct s_node
{
	int			coder_id;
	long long	priority_value;
}	t_node;

typedef struct s_heap
{
	t_node	*nodes;
	int		size;
	int		capacity;
}	t_heap;

void    init_data(t_data *data, char **argv);
int init_main(t_data *data, int argc, char **argv);
int ft_isnumber(char *s);
int check_global(int argc, char **argv);

#endif