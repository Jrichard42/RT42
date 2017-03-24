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

#include "light.h"
#include "plane.h"
#include "reflexion.h"
#include "refraction.h"

# define RECURSION_MAX 5

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

int				is_shadow(t_obj *obj
									, t_inter *inter,
									t_list *list,
									t_ray *ray_obj)
{
	int					shadow;
	double				tmp;
	t_obj				*tmp_obj;

	shadow = 0;
	while (list)
	{
		tmp_obj = ((t_obj *)list->content);
		if (tmp_obj->is_src != 1)
		{
			if(!isnan(tmp = (tmp_obj->inter(tmp_obj, ray_obj))) 
			&& tmp >= 0.01 && (tmp * tmp) <=
			squared_length_vector3f(sub_vector3f(obj->pos, inter->impact)))
			{
				if (tmp_obj != inter->obj)
				{
					shadow = 1;
					break;
				}
			}
		}
		list = list->next;
	}
	return (shadow);
}

static	double		fresnel(t_inter *inter, t_ray *ray)
{
	double		r0;
	double		theta;
	double		n;

	r0 = powf((ray->ir - inter->obj->mat.ir) / (ray->ir +
		inter->obj->mat.ir), 2.0);
	theta = -dot_vector3f(inter->normal, ray->dir);
	if (ray->ir > inter->obj->mat.ir)
	{
		n = (double)ray->ir / (double)inter->obj->mat.ir;
		n = n * n * (1.0f - (theta * theta));
		if (n < 1.0)
			theta = sqrt(1.0 - n);
	}
	theta = 1.0f - theta;
	r0 = r0 + (1.0f - r0) * theta * theta * theta * theta * theta;
	return (r0);
}

static	t_vector3f	apply_light_annex(t_obj *obj,
										t_ray *ray,
										int rec_count,
										t_rt *rt)
{
	t_vector3f 	color;
	t_inter		inter;
	double		r0;
	t_ray		ray_obj;

	inter = get_inters(rt->objs->head, ray);
	color = create_vector3f(0,0,0);
	if (inter.obj != NULL)
	{
		r0 = fresnel(&inter, ray);
		ray_obj.start = inter.impact;
		ray_obj.dir = normalize_vector3f(sub_vector3f(obj->pos, inter.impact));
		if (is_shadow(obj, &inter, rt->objs->head, &ray_obj) != 1)
			color = mult_vector3f(obj->light.calc_light(obj, ray, &inter), 1);
		if (rec_count)
		{
			color = add_vector3f(color, mult_vector3f(apply_reflexion(obj,
				*ray, rec_count, rt), (1 + (1.0 - 1) * r0)));
			color = add_vector3f(color, mult_vector3f(apply_refraction(obj,
				*ray, rec_count, rt), 1.0f - (1 + (1.0 - 1) * r0)));
		}
	}
	return (color);
}

t_vector3f			apply_light(t_rt *rt,
							t_ray *ray,							
							int rec_count)
{
	t_list				*node;
	t_vector3f			color;
	t_obj				*obj;
	t_inter				inter;
	int 				count_color;

	node = rt->objs->head;
	count_color = 0;
	inter = get_inters(rt->objs->head, ray);
	color = create_vector3f(0, 0, 0);
	while (node)
	{
		obj = ((t_obj *)node->content);
		if (obj->is_src == 1)
		{
			color = add_vector3f(color,
				apply_light_annex(obj, ray, rec_count, rt));
			count_color++;
		}
		node = node->next;
	}
	color = div_vector3f(color, count_color);
	return (clamp_vector3f(color, 0, 255));
}