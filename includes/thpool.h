/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thpool.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 15:16:10 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/25 09:31:29 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THPOOL_H
# define THPOOL_H

# include <pthread.h>
# include "libft.h"

typedef struct		s_job
{
	void			(*do_job)(void *data);
	void			*data;
	int				filled; //bool
}					t_job;

typedef struct		s_thpool
{
	pthread_mutex_t	mutex;
	int				nb_jobs;
	int				head;
	int				tail;
	t_job			*jobs;
}					t_thpool;

t_thpool			*create_thpool(int nb_threads, int nb_jobs, int data_size);
int					push_job(t_thpool *pool, void (*func)(void *), void *data, int data_size);
t_job				*pull_job(t_thpool *pool);

#endif
