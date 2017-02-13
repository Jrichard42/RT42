/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thpool.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 15:15:57 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/13 11:38:45 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include "thpool.h"

void		push_job(t_thpool *pool, void (*func)(void *), void *data)
{
	pool->jobs[pool->tail].do_job = func;
	pool->jobs[pool->tail].data = data;
	++pool->tail;
}

static void			*do_job(void *data)
{
	t_thpool	*pool;
	void (*func)(void *);
	void		*param;

	pool = (t_thpool *)data;
	while (pool->head == pool->tail)
		;
	pthread_mutex_lock(pool->mutex);
	func = pool->jobs[pool->head].do_job;
	param = pool->jobs[pool->head].data;
	++pool->head;

	func(param);
	
	return (NULL);
}

t_thpool		*create_thpool(int nb_threads, int nb_jobs, int data_size)
{
	t_thpool	*new;
	pthread_t	thread;

	if (!(new = ft_memalloc(sizeof(*new))))
		return (NULL);
	if (!(new->jobs = ft_memalloc(sizeof(*new->jobs))))
		return (NULL);
	new->nb_jobs = nb_jobs;
	mutex = PTHREAD_MUTEX_INITIALIZER;
	while (nb_jobs)
	{
		if (!(new->jobs->data = ft_memalloc(sizeof(data_size))))
			return (NULL);
		--nb_jobs;
	}
	while (nb_threads)
	{
		if (pthread_create(&thread, NULL, do_job, new))
			return (NULL);
		if (pthread_detach(thread))
			return (NULL);
		--nb_threads;
	}
	return (new);
}
