/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 14:48:35 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/16 15:06:10 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "light.h"
#include "obj.h"
#include "inter.h"
#include "plane.h"

# define RECURSION_MAX 4

void			put_in_image(t_rt *rt, int x, int y, t_vector3f *color)
{
	unsigned int		pixel_pos;
	int					int_color;

	int_color = (unsigned char)(color->x) & 0xFF;
	int_color += ((unsigned char)(color->y) & 0x00FF) << 8;
	int_color += ((unsigned char)(color->z) & 0x0000FF) << 16;
	if ((x < rt->env.wh[0]) && y < (rt->env.wh[1]))
	{
		pixel_pos = y * (rt->env.pitch / sizeof(unsigned int)) + x;
		rt->env.pixels[pixel_pos] = int_color;
	}
}

static	int				if_shadow(t_obj *obj
									, t_inter *inter,
									t_list *node,
									t_ray *ray_obj)
{
	int					shadow;
	double				tmp;

	shadow = 0;
	while (node)
	{
		if (((t_obj *)node->content)->is_src != 1)
		{
			if(!isnan(tmp = (((t_obj *)node->content)->inter(((t_obj *)node->content), ray_obj))) 
			&& tmp > 0.01 && (tmp * tmp) <
			squared_length_vector3f(sub_vector3f(obj->pos, inter->impact)))
			{
				if ((t_obj *)node->content != inter->obj)
				{
					shadow = 1;
					break;
				}
			}
		}
		node = node->next;
	}
	return (shadow);
}

// static	void		choose_texture(t_inter		*inter,
// 									float		*coeffs,
// 									t_list		*save,
// 									t_vector3f	*color)
// {
// 	if (((t_plane *)inter->obj->data)->damier == 1)
// 		*color = div_vector3f(add_vector3f(*color, calcul_light_procedurale(inter, coeffs,
// 			((t_obj *)save->content))), 2.0);
// 	else
// 		*color = div_vector3f(add_vector3f(*color, calcul_light(inter, coeffs,
// 			((t_obj *)save->content))), 2.0);
// }

// static	t_vector3f	apply_light_annex(t_list *save,
// 							t_ray ray,
// 							t_inter inter,
// 							int 	recursion_max)
// {
// 	float				coeffs;
// 	t_vector3f			color;
// 	int 				shadow;
// 	int					recursion;
// 	t_ray				ray_obj;

// 	color = create_vector3f(0, 0, 0);
// 	recursion = 0;
	// ray_obj.start = inter.impact;
	// ray_obj.dir = normalize_vector3f(sub_vector3f(((t_obj *)save->content)->
	// 	pos, inter.impact));
// 	shadow = if_shadow(save, &inter, save, &ray_obj);
// 	if (shadow != 1)
// 	{
// 		while (recursion < recursion_max)
// 		{
// 			if (inter.obj != NULL)
// 			{
// 				coeffs = calcul_coef(((t_obj *)save->content), &inter, &ray);
// 				ray.start = inter.impact;
// 				ray.dir = sub_vector3f(ray.dir, mult_vector3f(inter.normal,
// 					2.0 * dot_vector3f(ray.dir, inter.normal)));
// 				choose_texture(&inter, &coeffs, save, &color);
// 			}
// 			inter = get_inters(save, &ray);
// 			recursion++;
// 		}
// 	}
// 	return (color);
// }


int					calcul_cos_refraction(t_inter *inter, double *cos1, double *cos2, t_ray inc_tmp) // pour refraction
{
	t_vector3f	inc;

	inc = mult_vector3f(inc_tmp.dir, -1.0);
	*cos1 = dot_vector3f(inc, inter->normal);
	if (inter->obj->mat.ir == 0)
		return (-1);
	*cos2 = 1 - pow(inc_tmp.ir / inter->obj->mat.ir, 2.0) *
		(1.0 - pow(*cos1, 2.0));
	if (*cos2 < 0)
		return (-1);
	*cos2 = sqrt(*cos2);
	return (1);
}

static	t_vector3f	vector_ref(t_inter *inter, t_ray inc_tmp) // refraction aussi
{
	t_vector3f	v_refraction;
	double		cos1;
	double		cos2;
	double		ir_tmp;

	if (calcul_cos_refraction(inter, &cos1, &cos2, inc_tmp) == -1)
	{
		v_refraction.x = NAN;
		return (v_refraction);
	}
	ir_tmp = inter->obj->mat.ir;
	if (cos1 > 0)
		v_refraction =
		add_vector3f(mult_vector3f(inc_tmp.dir, inc_tmp.ir / ir_tmp),
		mult_vector3f(inter->normal, ((inc_tmp.ir / ir_tmp) * cos1) - cos2));
	else if (cos1 < 0)
		v_refraction =
		add_vector3f(mult_vector3f(inc_tmp.dir, inc_tmp.ir / ir_tmp),
		mult_vector3f(inter->normal, ((inc_tmp.ir / ir_tmp) * cos1) + cos2));
	else
		return (inc_tmp.dir);
	return (v_refraction);
}

static	t_vector3f	apply_refraction(t_obj *obj,
										t_ray ray,
										t_inter inter,
										t_list *list)
{
	t_vector3f	color;
	int 		recursion;
	t_ray		ray_ref;

	recursion = 0;
	color = create_vector3f(0,0,0);
	while (recursion < RECURSION_MAX)
	{
		if (inter.obj != NULL)
		{
			//ray.dir = vector_ref(&inter, ray);
			// ray.start = inter.impact;
			// ray.ir = inter.obj->mat.ir;
			// ray.dir = vector_ref(&inter, ray);
			if (inter.obj->mat.ir >= 1)
				if (!(isnan(ray.dir.x)))
					color = div_vector3f(add_vector3f(color, obj->light.calc_light(obj, &ray, &inter)), 2.0);
			ray.dir = vector_ref(&inter, ray);
			ray.start = inter.impact;
			ray.ir = inter.obj->mat.ir;
			//printf("color.x = %f, color.y = %f color.z = %f\n", color.x, color.y, color.z);
		}
		inter = get_inters(list, &ray);
		recursion++;
	}
	return (clamp_vector3f(color, 0, 255));
}

static	t_vector3f	apply_reflexion(t_obj *obj,
										t_ray ray,
										t_inter inter,
										t_list *list)
{
	t_vector3f	color;
	int			recursion;

	recursion = 0;
	color = create_vector3f(0,0,0);
	while (recursion < RECURSION_MAX)
	{
		if (inter.obj != NULL)
		{
			color = div_vector3f(add_vector3f(color, obj->light.calc_light(obj, &ray, &inter)), 2.0);
			ray.start = inter.impact;
			ray.dir = sub_vector3f(ray.dir, mult_vector3f(inter.normal,
				2.0 * dot_vector3f(ray.dir, inter.normal)));
		}
		inter = get_inters(list, &ray);
		recursion++;
	}
	return (clamp_vector3f(color, 0, 255));
}

static	t_vector3f	apply_light_annex(t_obj *obj,
										t_ray *ray,
										t_inter *inter,
										t_list *list)
{
	t_vector3f 	color;
	int			shadow;
	t_ray		ray_obj;

	color = create_vector3f(0,0,0);
	ray_obj.start = inter->impact;
	ray_obj.dir = normalize_vector3f(sub_vector3f(obj->pos, inter->impact));
	shadow = if_shadow(obj, inter, list, &ray_obj);
	if (shadow != 1)
	{
		color = mult_vector3f(obj->light.calc_light(obj, ray, inter), 0.7); // COULEUR DE BASE
		color = add_vector3f(color, mult_vector3f(apply_reflexion(obj, *ray, *inter, list), 0.3)); // COULEUR REFLEXION
	}
	//color = add_vector3f(color, mult_vector3f(apply_refraction(obj, *ray, *inter, list), 1)); // COULEUR REFRACTION A CORRIGER, NE MARCHE PAS !
	return (color);
}

t_vector3f			apply_light(t_rt *rt,
							t_ray *ray,
							t_inter inter) // TOSEE
{
	t_list				*node;
	t_vector3f			color;
	t_obj				*obj;

	node = rt->objs->head;
	color = create_vector3f(0, 0, 0);
	if (inter.obj != NULL)
	{
		while (node)
		{
			obj = ((t_obj *)node->content);
			if (obj->is_src == 1)
			{
				color = div_vector3f(add_vector3f(color, apply_light_annex(obj, ray, &inter, rt->objs->head)), 2.0);
				//color = obj->light.calc_light(obj, ray, &inter);
			 	// 	color += reflection() * 0.33;
				// color += refraction() * 0.33;
		//		color = add_vector3f(color, apply_light_annex(save, *ray, inter, recursion_max));
			}
			node = node->next;
		}
	}
	return (clamp_vector3f(color, 0, 255));
}
