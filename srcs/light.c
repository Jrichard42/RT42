/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/23 15:16:30 by jrichard         ###   ########.fr       */
/*   Updated: 2017/02/25 14:24:47 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "inter.h"
#include "libft.h"
#include "procedurale.h"
#include "parser.h"

#define	LIGHT ((t_light *)obj->data)

static float		specular_light(t_obj *obj, t_inter *inter, t_ray *ray)
{
	t_vector3f		pos_cam;
	t_vector3f		incidence;
	t_vector3f		tmp;
	double			angle;

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

float		diffuse_light(t_obj *obj, t_inter *inter)
{
	t_vector3f		ray_light;
	float			angle;

	ray_light = normalize_vector3f(sub_vector3f(obj->pos, inter->impact));
	angle = dot_vector3f(ray_light, inter->normal);
	if (angle < 0)
		angle = 0;
	return (angle);
}

float		calcul_coef(t_obj *obj, t_inter *inter, t_ray *ray)
{
	float			diffuse;
	float			specular;
	float			coeffs;

	specular = 0.0;
	diffuse = diffuse_light(obj, inter) * inter->obj->mat.kd;
	if (dot_vector3f(inter->normal, sub_vector3f(obj->pos, inter->impact)) > 0)
		specular = specular_light(obj, inter, ray) * inter->obj->mat.ks;
	coeffs = (diffuse + specular + inter->obj->mat.ka);
	return (coeffs);
}

t_vector3f	calcul_light(t_obj *obj, t_ray *ray, t_inter *inter)
{
	t_vector3f		color_return;
	float			coeffs;

	coeffs = calcul_coef(obj, inter, ray);
	color_return = mult_vector3f(mult_vector3f(inter->obj->color, coeffs), obj->light.intensity);
	return (color_return);
}

t_vector3f	calcul_light_procedurale(t_inter *inter, float *coeffs, t_obj *obj)
{
	t_vector3f		color_return;

	color_return = procedurale(inter, coeffs, &LIGHT->intensity);
	return (color_return);
}

static int			create_light2(t_kvlexer *token, t_rt *rt, t_obj *obj)
{
	if (!get_material(token, rt, &(obj->mat)))
		return (0);
	if (!get_as_vector3f(token, "POS", &(obj->pos)))
		return ((int)ft_error("The LIGHT should contain a field POS"));
	if (!get_as_int(token, "ID", &(obj->id)))
		return ((int)ft_error("The LIGHT should contain a field ID"));
	if (!get_as_int(token, "IS_SRC", &(obj->is_src)))
		return ((int)ft_error("The LIGHT should contain a field IS_SRC"));
	if (obj->is_src)
		obj->light = get_light(token);
	if (!get_as_int(token, "IS_VISIBLE", &(obj->is_visible)))
		return ((int)ft_error("The LIGHT should contain a field IS_VISIBLE")); //???
	if (!get_as_vector3f(token, "COLOR", &(obj->light.color)))
		return ((int)ft_error("The LIGHT should contain a field COLOR"));
	if (!get_as_float(token, "INTENSITY", &(obj->light.intensity)))
		return ((int)ft_error("The LIGHT should contain a field INTENSITY"));
	return (1);	
}

int					create_light(t_kvlexer *token, t_rt *rt)
{
	t_obj			obj;

	obj.normal = NULL;
	obj.inter = NULL;
	if (create_light2(token, rt, &obj))
		ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	else
		return (0);
	return (1);
}

