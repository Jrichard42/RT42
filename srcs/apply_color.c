/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 14:48:35 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/09 14:48:37 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "light.h"
#include "obj.h"
#include "inter.h"
#include "plane.h"
#include "apply_color.h"
#include "bruit_perlin.h"

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

static	int				if_shadow(t_list *node_obj
								, t_inter *inter,
								t_list *node,
								t_ray *ray_obj)
{
	int					shadow;
	double				tmp;

	shadow = 0;
	while (node_obj)
	{
		if (((t_obj *)node_obj->content)->is_src != 1)
		{
			if(!isnan(tmp = ((t_obj *)node_obj->content)->
				inter(((t_obj *)node_obj->content), ray_obj)) 
			&& tmp > 0.01 && (tmp * tmp) <
			squared_length_vector3f(sub_vector3f(((t_obj *)
				node->content)->pos, inter->impact)))
			{
				if (((t_obj *)node_obj->content) != inter->obj)
				{
					shadow = 1;
					break;
				}
			}
		}
		node_obj = node_obj->next;
	}
	return (shadow);
}

static	void		choose_texture(t_inter		*inter,
									float		*coeffs,
									t_list		*save,
									t_vector3f	*color)
{
	if (((t_plane *)inter->obj->data)->damier == 1)
		*color = div_vector3f(add_vector3f(*color, calcul_light_procedurale(inter, coeffs,
			((t_obj *)save->content))), 2.0);
	else
		*color = div_vector3f(add_vector3f(*color, calcul_light(inter, coeffs,
			((t_obj *)save->content))), 2.0);
}

static	t_vector3f	apply_light_annex(t_list *save,
							t_ray ray,
							t_inter inter,
							int 	recursion_max,
							t_rt *rt)
{
	// static t_vector3f	**texture;
	// static	int 		tmp_yolo;
	float				coeffs;
	t_vector3f			color;
	int 				shadow;
	int					recursion;
	t_ray				ray_obj;

	color = create_vector3f(0, 0, 0);
	recursion = 0;
	ray_obj.start = inter.impact;
	ray_obj.dir = normalize_vector3f(sub_vector3f(((t_obj *)save->content)->
		pos, inter.impact));
	shadow = if_shadow(save, &inter, save, &ray_obj);
	if (shadow != 1)
	{
		while (recursion < recursion_max)
		{
			if (inter.obj != NULL)
			{
				coeffs = calcul_coef(((t_obj *)save->content), &inter, &ray);
				ray.start = inter.impact;
				ray.dir = sub_vector3f(ray.dir, mult_vector3f(inter.normal,
					2.0 * dot_vector3f(ray.dir, inter.normal)));
				choose_texture(&inter, &coeffs, save, &color);
				color = mult_vector3f(add_vector3f(color, inter.obj->texture(inter.obj, inter)), coeffs / 2);
				//printf("coucou\n");
			}
			inter = get_inters(save, &ray);
			recursion++;
		}
	}
	// faudrais voir pour la mettre ici
	return (color);
}

t_vector3f			apply_light(t_rt *rt,
							t_ray *ray,
							t_inter inter,
							int 	recursion_max)
{
	t_list				*save;
	t_vector3f			color;

	save = rt->objs->head;
	color = create_vector3f(0, 0, 0);
	if (inter.obj != NULL)
	{
		while (save)
		{
			if (((t_obj *)save->content)->is_src == 1)
				color = add_vector3f(color, apply_light_annex(save, *ray, inter, recursion_max, rt));
			save = save->next;
		}
	}
	return (clamp_vector3f(color, 0, 255));
}