/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural_fonction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:54:10 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/13 15:54:12 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "rt.h"
#include "light.h"
#include "bruit_perlin.h"

unsigned int	marble(t_vector2f pixel, double noise[noiseheight][noisewidth])
{
	t_vector2d	period;
	double		turbpower;
	double		turbsize;
	double		xyvalue;
	double		sinevalue;

	period.x = 5.0;
	period.y = 10.0;
	turbpower = 10.0;
	turbsize = 64.0;
	if (pixel.y <= 1920 && pixel.y <= 1080)
	{
		xyvalue = (pixel.x * period.x / noisewidth + pixel.y * period.y / noiseheight + turbpower * turbulence(pixel.x, pixel.y, turbsize, noise)) / 256;
		sinevalue = 256 * fabs(sin(xyvalue * M_PI));
		return ((unsigned int)sinevalue);
	}
	return (0);
}

unsigned int	wood(t_vector2f pixel, double noise[noiseheight][noisewidth])
{
	double		xyperiode;
	double		turbpower;
	double		turbsize;
	t_vector2f	value;
	t_vector2f	dist_and_sine_value;

	xyperiode = 12.0;
	turbpower = 0.05;
	turbsize = 24.0;
	if (pixel.y <= 1920 && pixel.y <= 1080)
	{
		value.x = (pixel.x - noisewidth / 2) / (double)noisewidth;
		value.y = (pixel.y - noiseheight / 2) / (double)noiseheight;
		dist_and_sine_value.x = sqrt(value.x * value.x + value.y * value.y) + turbpower * turbulence(pixel.x, pixel.y, turbsize, noise) / 256.0;
		dist_and_sine_value.y = 128.0 * fabs(sin(2 * xyperiode * dist_and_sine_value.x * M_PI));
		return ((unsigned int) dist_and_sine_value.y);
	}
	return (0);
}
