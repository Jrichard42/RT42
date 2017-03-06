/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:25:03 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/06 12:06:27 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "camera.h"
#include "thread_manager.h"
#include "libft.h"

#define NB_THREAD 100
#define THREAD_DATA ((t_thread_data *)data)

void					thread_manager(t_rt *rt)
{
	pthread_t			threads[NB_THREAD];
	t_thread_data		data[NB_THREAD];
	int					fullsize;
	int					i;

	i = 0;
	fullsize = WIN_X * WIN_Y;
	while (i < NB_THREAD)
	{
		data[i].rt = rt;
		data[i].index = (fullsize / NB_THREAD) * i;
		data[i].size = fullsize / NB_THREAD;
		if (i == NB_THREAD - 1)
			data[i].size += fullsize % NB_THREAD;
		pthread_create(&threads[i], NULL, &render_chunk, (void *)&data[i]);
		++i;
	}
	i = 0;
	while (i < NB_THREAD)
		pthread_join(threads[i++], NULL);
}
