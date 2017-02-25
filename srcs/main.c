/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:26:17 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/23 14:56:11 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "thpool.h"
#include "rt.h"

static int		loop(t_rt *rt, t_thpool *pool)
{
	refresh_rt(rt, pool);
	while (1)
	{
		if (!check_events())
			return (0);
		render_rt(rt);
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_thpool	*pool;
	t_rt		*rt;

	if (argc != 2)
		return (-1);
	if (!(rt = create_rt(1920, 1080, argv[1])))
		return (1);
	pool = create_thpool(10, 100000, sizeof(t_thread_data));
	loop(rt, pool);
	// fontion destruction en attente
	return (0);
}
