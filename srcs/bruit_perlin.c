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

void			rand_noise(double ***noise, t_vector2f size)
{
	int		x;
	int		y;

	y = -1;
	while (++y < size.y)
	{
		x = -1;
		while (++x < size.x)
			*noise[y][x] = (lrand48() % 32768) / 32768.0;
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

// t_vector3f		bruit_perlin(t_kvlexer *token, t_rt, *rt, t_texture *tex)

int			bruit_perlin(t_vector2f size, char *type, double ***noise)
{
	static	int		marque;
	t_vector3f		color;
	t_vector2f		point;

	if (marque != 1)
	{
		point.y = -1;
		if (!(*noise = (t_vector3f **)malloc(sizeof(t_vector3f *) * size.y)))
			return (-1);
		while (++point.y < size.y)
		{
			point.x = 0;
			if (!(*noise[(int)point.y] = (t_vector3f *)malloc(sizeof(t_vector3f) * size.x)))
				return (-1);
			while (point.x < size.x)
				point.x++;
		}
		rand_noise(noise, size);
		marque = 1;
	}
	return (1);
}
