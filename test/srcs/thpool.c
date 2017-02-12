/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thpool.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 15:15:57 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/12 18:25:20 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include "thpool.h"

void		push_job(t_thpool *pool, void (*func)(void *), void *data)
{
	t_job	new;

	if (!pool->job)
	{
	}






	t_job	new;

	new.do_job = func;
	new.data = data;
	ft_lstadd_end(&(pool->jobs), ft_lstnew(&new, sizeof(new)));
}

t_job		*pull_job(t_thpool *pool)
{
	
}

static void			*do_job(void *data)
{
	t_thpool	*pool;

	pool = (t_thpool *)data;
	while (!pool->jobs)
		printf("empty\n");
	printf("doing stuff\n");
	return (NULL);
}

t_thpool		*create_thpool(int nb)
{
	t_thpool	*new;
	pthread_t	thread;

	if (!(new = ft_memalloc(sizeof(*new))))
		return (NULL);
	while (nb)
	{
		if (pthread_create(&thread, NULL, do_job, new))
			return (NULL);
		if (pthread_detach(thread))
			return (NULL);
		--nb;
	}
	return (new);
}
