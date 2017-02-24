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
#include "plane.h"
#include "inter.h"

static t_vector3f	procedure_calcul_light_sup(float impact, float *coeffs, float *intensity, t_inter *inter)
{
	t_vector3f		color_return;

	color_return = create_vector3f(0,0,0);
	if (sin(M_PI / 10.0) * sin((M_PI / 10.0) * impact) >= 0)
		color_return = mult_vector3f(mult_vector3f(((t_plane *)inter->obj->data)->color1, *coeffs), *intensity);
	else
		color_return = mult_vector3f(mult_vector3f(((t_plane *)inter->obj->data)->color2, *coeffs), *intensity);
	return (color_return);
}

static t_vector3f	procedure_calcul_light_inf(float impact, float *coeffs, float *intensity, t_inter *inter)
{
	t_vector3f		color_return;

	color_return = create_vector3f(0,0,0);
	if (sin(M_PI / 10.0) * sin((M_PI / 10.0) * impact) >= 0)
		color_return = mult_vector3f(mult_vector3f(((t_plane *)inter->obj->data)->color2, *coeffs), *intensity);
	else
		color_return = mult_vector3f(mult_vector3f(((t_plane *)inter->obj->data)->color1, *coeffs), *intensity);
	return (color_return);
}

static t_vector3f	procedurale_inf_zero(t_inter *inter, float *coeffs, float *intensity)
{
	t_vector3f color_return;

	color_return = create_vector3f(0,0,0);
	if (inter->normal.y != 0)
		color_return = procedure_calcul_light_inf(inter->impact.x, coeffs, intensity, inter);
	else if ((inter->normal.y == 0) && (inter->normal.z == 0))
		color_return = procedure_calcul_light_inf(inter->impact.y, coeffs, intensity, inter);
	else if (((inter->normal.y == 0) && (inter->normal.x == 0)))
		color_return = procedure_calcul_light_inf(inter->impact.y, coeffs, intensity, inter);
	return (color_return);
}

static t_vector3f	procedurale_sup_zero(t_inter *inter, float *coeffs, float *intensity)
{
	t_vector3f color_return;

	color_return = create_vector3f(0,0,0);
	if (inter->normal.y != 0)
		color_return = procedure_calcul_light_sup(inter->impact.x, coeffs, intensity, inter);
	else if ((inter->normal.y == 0) && (inter->normal.z == 0))
		color_return = procedure_calcul_light_sup(inter->impact.y, coeffs, intensity, inter);
	else if (((inter->normal.y == 0) && (inter->normal.x == 0)))
		color_return = procedure_calcul_light_sup(inter->impact.y, coeffs, intensity, inter);
	return (color_return);
}

t_vector3f			procedurale(t_inter *inter, float *coeffs, float *intensity)
{
	t_vector3f		color_return;

	if (((inter->normal.y != 0) || (inter->normal.x != 0)))
	{
		if ((sin(M_PI / 10.0) * sin((M_PI / 10.0) * inter->impact.z)) >= 0)
			color_return = procedurale_sup_zero(inter, coeffs, intensity);
		else
			color_return = procedurale_inf_zero(inter, coeffs, intensity);
	}
	if (((inter->normal.y == 0) && (inter->normal.x == 0)))
	{
		if ((sin(M_PI / 10.0) * sin((M_PI / 10.0) * inter->impact.x)) >= 0)
			color_return = procedurale_sup_zero(inter, coeffs, intensity);
		else
			color_return = procedurale_inf_zero(inter, coeffs, intensity);
	}
	return (color_return);
}