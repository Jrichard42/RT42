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

void free_tab(double **noise, t_vector2f size)
{
	t_vector2f point;
	if (noise)
	{
		point.y = 0;
		while (point.y <= size.y)
		{
			if (noise[(int)point.y])
				free(noise[(int)point.y]);
			point.y++;
		}
	free(noise);
	}
}

void				rand_noise(double ***noise, t_vector2f size)
{
	int				x;
	int				y;

	y = -1;
	while (++y < size.y)
	{
		x = -1;
		while (++x < size.x)
			(*noise)[y][x] = (lrand48() % 32768) / 32768.0;
	}
}

double				smooth_noise(double x,
								double y,
								double **noise,
								t_vector2f size)
{
	double			fract_x;
	double			fract_y;
	t_vector2i		tmp1;
	t_vector2i		tmp2;
	double			value;

	fract_x = x - (int)x;
	fract_y = y - (int)y;
	tmp1.x = ((int)x + (int)size.x) % (int)size.x;
	tmp1.y = ((int)y + (int)size.y) % (int)size.y;
	tmp2.x = (tmp1.x + (int)size.x - 1) % (int)size.x;
	tmp2.y = (tmp1.y + (int)size.y - 1) % (int)size.y;
	value = 0.0;
	value += fract_x * fract_y * noise[tmp1.y][tmp1.x];
	value += (1 - fract_x) * fract_y * noise[tmp1.y][tmp2.x];
	value += fract_x * (1 - fract_y) * noise[tmp2.y][tmp1.x];
	value += (1 - fract_x) * (1 - fract_y) * noise[tmp2.y][tmp2.x];
	return (value);
}

double				turbulence(t_vector2f pixel,
							double size,
							double **noise,
							t_vector2f size_tex)
{
	double			value;
	double			initial_size;

	initial_size = size;
	value = 0.0;
	while (size >= 1)
	{
		value += smooth_noise(pixel.x / size, pixel.y
			/ size, noise, size_tex) * size;
		size /= 2.0;
	}
	return (128.0 * value / initial_size);
}

int					bruit_perlin(t_vector2f size, double ***noise)
{
	int				y;

	y = 0;
	if (!(*noise = (double **)malloc(sizeof(double *) * size.y)))
		return (0);
	while (y < size.y)
	{
		if (!((*noise)[y] = (double *)malloc(sizeof(double) * size.x)))
			return (0);
		y++;
	}
	rand_noise(noise, size);
	return (1);
}
