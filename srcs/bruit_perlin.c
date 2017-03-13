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
#include "camera.h"
#include "light.h"
#include "bruit_perlin.h"
#define noisewidth WIN_X
#define noiseheight WIN_Y

float			color_hsl(float tmp_color, float tmp1, float tmp2)
{
	float		color;

	color = 0.0;
	if ((6 * tmp_color) < 1)
		color = tmp2 + (tmp1 - tmp2) * 6 * tmp_color;
	else if ((2 * tmp_color) < 1)
		color = tmp1;
	else if ((3 * tmp_color) < 2)
		color = tmp2 + (tmp1 - tmp2) * (0.666 - tmp_color) * 6;
	else
		color = tmp2;
	color = color * 255.0;
	return (color);
}

void			rand_noise(double noise[noiseheight][noisewidth])
{
	int		x;
	int		y;

	y = 0;
	while (y < noiseheight)
	{
		x = 0;
		while (x < noisewidth)
		{
			noise[y][x] = (rand() % 32768) / 32768.0;
			x++;
		}
		y++;
	}
}

double			smooth_noise(double x,
								double y,
								double noise[noiseheight][noisewidth])
{
	double		fract_x;
	double		fract_y;
	t_vector2i	tmp1;
	t_vector2i	tmp2;
	double		value;

	fract_x = x - (int)x;
	fract_y = y - (int)y;
	tmp1.x = ((int)x + noisewidth) % noisewidth;
	tmp1.y = ((int)y + noiseheight) % noiseheight;
	tmp2.x = (tmp1.x + noisewidth - 1) % noisewidth;
	tmp2.y = (tmp1.y + noiseheight - 1) % noiseheight;
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
							double noise[noiseheight][noisewidth])
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

t_vector3f		bruit_perlin(t_vector2f pixel)
{
	static	int		marque;
	static	double	noise[noiseheight][noisewidth];
	t_vector3f		color;
	float			l;

	if (marque != 1)
	{
		rand_noise(noise);
		marque = 1;
	}
	if (pixel.y <= 1920 && pixel.y <= 1080)
	{
		// l = (192 + (unsigned int)(
		// 	turbulence(pixel.x, pixel.y, 64, noise))) / 4;
		// if (l > 100)
		// 	l = 100;
		// color = hsl_to_rgb(240, 100, l);
		color.x = 30 + marble(pixel, noise);			//pour le marble on peut utilser le rgb
		color.y = 10 + marble(pixel, noise);			//pour le marble on peut utilser le rgb
		color.z = marble(pixel, noise);					//pour le marble on peut utilser le rgb
		// color.x = 130 + wood(pixel, noise);			//pour le marble on peut utilser le rgb
		// color.y = 60 + wood(pixel, noise);			//pour le marble on peut utilser le rgb
		// color.z = 19;								//pour le marble on peut utilser le rgb
	}
	cap_light(&color);
	return (color);
}
