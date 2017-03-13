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
#define noisewidth 1920
#define noiseheight 1080

float			color_HSL(float tmp_color, float tmp1, float tmp2)
{
	float 		color;

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

t_vector3f		HSL_TO_RGB(float h, float s, float l)
{
	float		tmp1;
	float		tmp2;
	t_vector3f	tmp3;
	t_vector3f	color;
	float		hue;

	tmp1 = 0.0;
	l = fabs(l) / 100;
	s = fabs(s) / 100;
	if (s > 1.0)
		s = 1.0;
	if (l < 0.5)
		tmp1 = l * (1.0 + s);
	else
		tmp1 = (l + s) - (l * s);
	tmp2 = 2 * l - tmp1;
	hue = h / 360;
	tmp3.x = hue + 0.333;
	tmp3.y = hue;
	tmp3.z = hue - 0.333;
	color.x = color_HSL(tmp3.x, tmp1, tmp2);
	color.y = color_HSL(tmp3.y, tmp1, tmp2);
	color.z = color_HSL(tmp3.z, tmp1, tmp2);
	return (color);
}

void			rand_noise(double noise[noiseheight][noisewidth])
{
	int		x;
	int		y;

	y = 0;
	while(y < noiseheight)
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

double			smooth_noise(double x, double y, double noise[noiseheight][noisewidth])
{
	double		fract_x;
	double		fract_y;
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	double		value;

	fract_x = x - (int)x;
	fract_y = y - (int)y;
	x1 = ((int)x + noisewidth) % noisewidth;
	y1 = ((int)y + noiseheight) % noiseheight;
	x2 = (x1 + noisewidth - 1) % noisewidth;
	y2 = (y1 + noiseheight - 1) % noiseheight;
	value = 0.0;
	value += fract_x * fract_y * noise[y1][x1];
	value += (1 - fract_x) * fract_y * noise[(int)y1][(int)x2];
	value += fract_x * (1 - fract_y) * noise[(int)y2][(int)x1];
	value += (1 - fract_x) * (1 - fract_y) * noise[(int)y2][(int)x2];
	return (value);
}

double			turbulence(double x, double y, double size, double noise[noiseheight][noisewidth])
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
		l = (192 + (unsigned int)(turbulence(pixel.x, pixel.y, 128, noise))) / 4;
		if (l > 100)
			l = 100;
		color = HSL_TO_RGB(240, 100, l);
	}
	cap_light(&color);
	return (color);
}