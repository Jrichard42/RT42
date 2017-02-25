/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thpool.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 15:15:57 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/25 11:16:11 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thpool.h"

int				push_job(t_thpool *pool, void (*func)(void *),
		void *data, int data_size)
{
	int			tail;

	pthread_mutex_lock(&pool->mutex_tail);
	if (pool->jobs[pool->tail].filled == 0)
	{
		tail = pool->tail;
		pool->jobs[tail].filled = 1;
		if (pool->tail == pool->nb_jobs - 1)
			pool->tail = 0;
		else
			++pool->tail;
		pthread_mutex_unlock(&pool->mutex_tail);
		pool->jobs[tail].do_job = func;
		ft_memcpy(pool->jobs[tail].data, data, data_size);
	}
	else
		pthread_mutex_unlock(&pool->mutex_tail);	
	return (1);
}

static void		*do_job(void *data)
{
	t_thpool	*pool;
	void 		(*func)(void *);
	void		*param;

	pool = (t_thpool *)data;
	while (1)
	{
		func = NULL;
		param = NULL;
		pthread_mutex_lock(&pool->mutex_head);
		if (pool->jobs[pool->head].filled == 1)
		{
			func = pool->jobs[pool->head].do_job;
			param = pool->jobs[pool->head].data;
			pool->jobs[pool->head].filled = 0;
			pthread_mutex_unlock(&pool->mutex_head);
			if (pool->head == pool->nb_jobs - 1)
				pool->head = 0;
			else
				++pool->head;
			if (func)
				func(param);
		}
		else
			pthread_mutex_unlock(&pool->mutex_head);
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
	new->mutex_head = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	new->mutex_tail = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	while (nb_jobs)
	{
		if (!(new->jobs[nb_jobs - 1].data = ft_memalloc(data_size)))
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
