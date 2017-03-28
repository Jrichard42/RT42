/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 15:12:17 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/27 17:38:01 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inter.h"
#include "libft.h"
#include "parser.h"

static float			specular_light(t_obj *obj, t_inter *inter, t_ray *ray)
{
	t_vector3f			pos_cam;
	t_vector3f			incidence;
	t_vector3f			tmp;
	double				angle;

	pos_cam = sub_vector3f(ray->start, inter->impact);
	incidence = sub_vector3f(inter->impact, obj->pos);
	tmp = mult_vector3f(inter->normal, 2.0);
	tmp = mult_vector3f(tmp, dot_vector3f(inter->normal, incidence));
	tmp = sub_vector3f(incidence, tmp);
	tmp = normalize_vector3f(tmp);
	pos_cam = normalize_vector3f(pos_cam);
	angle = dot_vector3f(pos_cam, tmp);
	if (angle < 0)
		angle = 0;
	angle = powf(angle, inter->obj->mat.sh);
	return (angle);
}

static float			diffuse_light(t_obj *obj, t_inter *inter)
{
	t_vector3f			ray_light;
	float				angle;

	ray_light = normalize_vector3f(sub_vector3f(obj->pos, inter->impact));
	angle = dot_vector3f(ray_light, inter->normal);
	if (angle < 0)
		angle = 0;
	return (angle);
}

t_vector3f				calcul_coef(t_obj *obj, t_inter *inter, t_ray *ray)
{
	t_vector3f			diffuse;
	t_vector3f			specular;
	t_vector3f			coeffs;

	specular = create_vector3f(0, 0, 0);
	diffuse = mult_vector3f(inter->obj->mat.kd, diffuse_light(obj, inter));
	if (dot_vector3f(inter->normal, sub_vector3f(obj->pos, inter->impact)) > 0)
		specular = mult_vector3f(inter->obj->mat.ks,
			specular_light(obj, inter, ray));
	coeffs = add_vector3f(add_vector3f(diffuse, specular), inter->obj->mat.ka);
	return (coeffs);
}
