/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsl_to_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:54:44 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/13 15:56:02 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "rt.h"
#include "light.h"
#include "bruit_perlin.h"

t_vector3f		hsl_to_rgb(float h, float s, float l)
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
	color.x = color_hsl(tmp3.x, tmp1, tmp2);
	color.y = color_hsl(tmp3.y, tmp1, tmp2);
	color.z = color_hsl(tmp3.z, tmp1, tmp2);
	return (color);
}
