/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_polygone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 16:25:20 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/30 19:02:11 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle.h"
#include "pyramide.h"
#include "tetraedre.h"

static	int	if_colision_pyra(t_pyra *pyra, int i, t_ray ray)
{
	float	dist;
	int		j;

	j = 0;
	while (j < 6)
	{
		if (j != i && !isnan(dist = inter_triangles(&pyra->face[j], &ray))
			&& dist > 0)
		{
			pyra->face[i].normal = mult_vector3f(pyra->face[i].normal, -1);
			return (1);
		}
		j++;
	}
	return (0);
}

void		calc_normal_pyra(t_pyra *pyra)
{
	t_vector3f	e1;
	t_vector3f	e2;
	t_ray		ray;
	int			i;

	i = 0;
	while (i < 6)
	{
		e1 = sub_vector3f(pyra->face[i].vertex[1], pyra->face[i].vertex[0]);
		e2 = sub_vector3f(pyra->face[i].vertex[2], pyra->face[i].vertex[0]);
		ray.dir = normalize_vector3f(cross_vector3f(e1, e2));
		pyra->face[i].normal = ray.dir;
		ray.start = div_vector3f(add_vector3f(pyra->face[i].vertex[1],
		pyra->face[i].vertex[0]), 2.0f);
		ray.start = div_vector3f(add_vector3f(ray.start,
			pyra->face[i].vertex[2]), 2.0f);
		if_colision_pyra(pyra, i, ray);
		i++;
	}
}

static	int	if_colision_tetra(t_tetra *tetra, int i, t_ray ray)
{
	float	dist;
	int		j;

	j = 0;
	while (j < 4)
	{
		if (j != i && !isnan(dist = inter_triangles(&tetra->face[j], &ray))
			&& dist > 0)
		{
			tetra->face[i].normal = mult_vector3f(tetra->face[i].normal, -1);
			return (1);
		}
		j++;
	}
	return (0);
}

void		calc_normal_tetra(t_tetra *tetra)
{
	t_vector3f	e1;
	t_vector3f	e2;
	t_ray		ray;
	int			i;

	i = 0;
	while (i < 4)
	{
		e1 = sub_vector3f(tetra->face[i].vertex[1], tetra->face[i].vertex[0]);
		e2 = sub_vector3f(tetra->face[i].vertex[2], tetra->face[i].vertex[0]);
		ray.dir = normalize_vector3f(cross_vector3f(e1, e2));
		tetra->face[i].normal = ray.dir;
		ray.start = div_vector3f(add_vector3f(tetra->face[i].vertex[1],
		tetra->face[i].vertex[0]), 2.0f);
		ray.start = div_vector3f(add_vector3f(ray.start,
			tetra->face[i].vertex[2]), 2.0f);
		if_colision_tetra(tetra, i, ray);
		i++;
	}
}
