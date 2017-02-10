/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:26:17 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/09 17:08:42 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		main(int argc, char **argv)
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
