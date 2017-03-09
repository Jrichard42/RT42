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
#include "plane.h"

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
			&& tmp > 0.01 && (tmp * tmp) < squared_length_vector3f(sub_vector3f(((t_obj *)
				node->content)->pos, inter->impact)))
			{
				if (((t_obj *)node_obj->content)->id != inter->obj->id)
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

void			apply_light(t_rt *rt,
							t_ray *ray,
							t_vector3f *color,
							t_inter *inter)
{
	int 				shadow;
	t_list				*save;
	float				coeffs;
	t_list				*node_obj;
	t_ray				ray_obj;

	save = rt->objs->head;;
	if (inter->obj != NULL)
	{
		while (save)
		{
			if (((t_obj *)save->content)->is_src == 1)
			{
				node_obj = save;
				ray_obj.start = inter->impact;
				ray_obj.dir = normalize_vector3f(sub_vector3f(((t_obj *)save->content)->pos, inter->impact));
				shadow = if_shadow(node_obj, inter, save, &ray_obj);
				if (shadow != 1)
				{
					coeffs = calcul_coef(((t_obj *)save->content), inter, ray);
					if (((t_plane *)inter->obj->data)->damier == 1)
					 	*color = add_vector3f(calcul_light_procedurale(inter, &coeffs, ((t_obj *)save->content)), *color);
					*color = add_vector3f(calcul_light(inter, &coeffs, ((t_obj *)save->content)), *color);
					*color = clamp_vector3f(*color, 0, 255);
				}
				shadow = 0;
			}
			save = save->next;
		}
	}
}