/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:26:17 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/12 18:46:29 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "rt.h"

static int		loop(t_rt *rt)
{
	texture_refresh(rt);
	while (1)
	{
		if (!check_events())
			return (0);
		render(rt->env);
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_rt		rt;

	if (argc != 2)
		return (-1);
	rt.env.size.x = 1300;
	rt.env.size.y = 1300;
	if (parser(argv[1], &rt) == -1)	// fonction parser TODO
		return (-1);
	win_init(&rt);
	loop(&rt);
	// fontion destruction en attente
	return (0);
}
