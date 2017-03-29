/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:26:17 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/09 17:35:47 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "rt.h"

static int		loop(t_rt *rt)
{
	refresh_rt(rt);
	while (1)
	{
		if (!check_events(rt))
			return (0);
		render_rt(rt);
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_rt	*rt;

	rt = NULL;
	if (argc != 2)
	{
		ft_putendl("Usage : ./rt scene_file");
		return (-1);
	}
	if ((rt = create_rt(WIN_X, WIN_Y, argv[1])))
		loop(rt);
	destroy_rt(rt);
	return (0);
}
