/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:40:45 by dbreton           #+#    #+#             */
/*   Updated: 2017/04/03 15:48:03 by dbreton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "apply_color.h"
#include "sampling.h"
#include "thread_manager.h"

#define T_DATA ((t_thread_data *)data)

void			*render_chunk(void *data)
{
	t_vector2f	pixel;
	t_vector3f	color;

	pixel = create_vector2f(T_DATA->index % WIN_X, T_DATA->index / WIN_X);
	while (T_DATA->size > 0)
	{
		if (pixel.x == WIN_X)
		{
			pixel.x = 0;
			++pixel.y;
		}
		color = sampling(T_DATA->rt, pixel, T_DATA->rt->camera->sampling);
		put_in_image(T_DATA->rt, pixel.x, pixel.y, &color);
		++pixel.x;
		--T_DATA->size;
	}
	return (NULL);
}
