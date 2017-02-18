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

	if (argc != 2)
		return (-1);
	rt = create_rt(1300, 1300, argv[1]);
	loop(rt);
	// fontion destruction en attente
	return (0);
}
