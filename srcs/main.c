/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:26:17 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/18 19:40:41 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "rt.h"
#include "opencl.h"

static int		loop(t_rt *rt)
{
	refresh_rt(rt);
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
	t_rt		*rt;
	t_cl		cl;

	if (argc != 2)
		return (-1);
	cl = cl_init("./kernels");
	printf("%x\n", (unsigned int)ht_get(cl.kernels, "hello"));

	rt = create_rt(1920, 1080, argv[1]);
	loop(rt);
	// fontion destruction en attente
	return (0);
}
