/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bruit_perlin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 15:26:01 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/10 15:26:02 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "light.h"
#include "bruit_perlin.h"

void			rand_noise(double noise[WIN_Y][WIN_X])
{
	int		x;
	int		y;

	y = 0;
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
			noise[y][x] = (lrand48() % 32768) / 32768.0;
			x++;
		}
		y++;
	}
}

double			smooth_noise(double x,
								double y,
								double noise[WIN_Y][WIN_X])
{
	double		fract_x;
	double		fract_y;
	t_vector2i	tmp1;
	t_vector2i	tmp2;
	double		value;

	fract_x = x - (int)x;
	fract_y = y - (int)y;
	tmp1.x = ((int)x + WIN_X) % WIN_X;
	tmp1.y = ((int)y + WIN_Y) % WIN_Y;
	tmp2.x = (tmp1.x + WIN_X - 1) % WIN_X;
	tmp2.y = (tmp1.y + WIN_Y - 1) % WIN_Y;
	value = 0.0;
	value += fract_x * fract_y * noise[tmp1.y][tmp1.x];
	value += (1 - fract_x) * fract_y * noise[tmp1.y][tmp2.x];
	value += fract_x * (1 - fract_y) * noise[tmp2.y][tmp1.x];
	value += (1 - fract_x) * (1 - fract_y) * noise[tmp2.y][tmp2.x];
	return (value);
}

double			turbulence(double x,
							double y,
							double size,
							double noise[WIN_Y][WIN_X])
{
	double		value;
	double		initial_size;

	initial_size = size;
	value = 0.0;
	while (size >= 1)
	{
		value += smooth_noise(x / size, y / size, noise) * size;
		size /= 2.0;
	}
	return (128.0 * value / initial_size);
}

t_vector3f		bruit_perlin(t_vector2f pixel, char *type)
{
	static	int		marque;
	static	double	noise[WIN_Y][WIN_X];
	t_vector3f		color;

	if (marque != 1)
	{
		rand_noise(noise);
		marque = 1;
	}
	// if (pixel.x <= 1920 && pixel.y <= 1080)
	color = select_texture(type, pixel, noise);
	// cap_light(&color);
	return (color);
}
