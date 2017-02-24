/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedurale.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:15:15 by abitoun           #+#    #+#             */
/*   Updated: 2017/02/24 18:15:16 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "obj.h"
#include "libft.h"
#include "rt.h"
#include "inter.h"

static t_vector3f	procedurale_inf_zero(float nbr, float coeffs, float intensity, t_vector3f *color)
{
	t_vector3f		color1;
	t_vector3f		color2;
	t_vector3f		color_return;

	color1 = create_vector3f(0,0,0);
	color2 = create_vector3f(255,255,255);
	if (nbr >= 0)
	{
		color_return = mult_vector3f(mult_vector3f(color2, coeffs), intensity);
		color_return = add_vector3f(color_return, *color);
	}
	else
	{
		color_return = mult_vector3f(mult_vector3f(color1, coeffs), intensity);
		color_return = add_vector3f(color_return, *color);
	}
	return (color_return);
}

static t_vector3f	procedurale_sup_zero(float nbr, float coeffs, float intensity, t_vector3f *color)
{
	t_vector3f		color1;
	t_vector3f		color2;
	t_vector3f		color_return;

	color1 = create_vector3f(0,0,0);
	color2 = create_vector3f(255,255,255);
	if (nbr >= 0)
	{
		color_return = mult_vector3f(mult_vector3f(color1, coeffs), intensity);
		color_return = add_vector3f(color_return, *color);
	}
	else
	{
		color_return = mult_vector3f(mult_vector3f(color2, coeffs), intensity);
		color_return = add_vector3f(color_return, *color);
	}
	return (color_return);
}

t_vector3f			procedurale(t_inter *inter, float coeffs, float intensity, t_vector3f *color)
{
	t_vector3f		color_return;

	if ((sin(M_PI / 20.0) * sin((M_PI / 20.0) * inter->impact.z)) >= 0)
		color_return = procedurale_sup_zero(sin(M_PI / 10.0) * sin((M_PI / 10.0) * inter->impact.x), coeffs, intensity, color);
	else
		color_return = procedurale_inf_zero(sin(M_PI / 10.0) * sin((M_PI / 10.0) * inter->impact.x), coeffs, intensity, color);
	return (color_return);
}