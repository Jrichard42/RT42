/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thpool.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 15:15:57 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/13 17:38:40 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "thpool.h"

int				push_job(t_thpool *pool, void (*func)(void *), void *data)
{
	pthread_mutex_lock(&pool->mutex);
	if (pool->filled == pool->nb_jobs)
	{
		printf("FAIL\n");
		return (-1);
	}
	pool->jobs[pool->tail].do_job = func;
	pool->jobs[pool->tail].data = data;
	if (pool->tail == pool->nb_jobs - 1)
		pool->tail = 0;
	else
		++pool->tail;
	++pool->filled;
	pthread_mutex_unlock(&pool->mutex);
	return (1);
}

static void			*do_job(void *data)
{
	t_thpool	*pool;
	void (*func)(void *);
	void		*param;


	pool = (t_thpool *)data;
	while (1)
	{
		func = NULL;
		param = NULL;
		pthread_mutex_lock(&pool->mutex);
		if (pool->filled)
		{
			--pool->filled;
			pthread_mutex_unlock(&pool->mutex);
			func = pool->jobs[pool->head].do_job;
			param = pool->jobs[pool->head].data;
			if (pool->head == pool->nb_jobs - 1)
				pool->head = 0;
			else
				++pool->head;
			--pool->filled;
			if (func)
				func(param);
		}
		else
			pthread_mutex_unlock(&pool->mutex);
	}
	return (NULL);
}

t_thpool		*create_thpool(int nb_threads, int nb_jobs, int data_size)
{
	t_thpool	*new;
	pthread_t	thread;

	if (!(new = ft_memalloc(sizeof(*new))))
		return (NULL);
	if (!(new->jobs = ft_memalloc(nb_jobs * sizeof(*new->jobs))))
		return (NULL);
	new->nb_jobs = nb_jobs;
	new->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
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
