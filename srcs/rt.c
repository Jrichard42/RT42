/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreton <dbreton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/19 19:15:07 by dbreton           #+#    #+#             */
/*   Updated: 2017/02/25 14:52:31 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "light.h"
#include "obj.h"
#include "inter.h"
#include "ray.h"
#include "plane.h"
#include "sphere.h"
#include "parser.h"	
#include "camera.h"

#define	LIGHT ((t_light *)((t_obj *)save->content)->data)
//TODO put in .h
t_vector3f		get_inters(t_rt *rt, t_ray *ray, int rec);

int                get_color_value(t_vector3f c)
{
	int            res;

	res = (unsigned char)(c.x) & 0xFF;
	res += ((unsigned char)(c.y) & 0x00FF) << 8;
	res += ((unsigned char)(c.z) & 0x0000FF) << 16;
	return (res);
}

void			calcul_inter(t_ray *ray, t_obj *obj, t_inter *inter)
{
	float 			tmp;

	tmp = obj->inter(obj, ray);
	if (!isnan(tmp) && tmp > 0.01 && (tmp < inter->distance || isnan(inter->distance)))
	{
		inter->distance = tmp;
		inter->impact = add_vector3f(ray->start, mult_vector3f(ray->dir, inter->distance));
		inter->normal = obj->normal(obj, &inter->impact);
		inter->obj = obj;
	}
}

static void				put_in_image(t_rt *rt, int x, int y, t_vector3f *color)
{
	unsigned int		pixel_pos;
	int					int_color;

	int_color = get_color_value(*color);
	if ((x < rt->env.wh[0]) && y < (rt->env.wh[1]))
	{
		pixel_pos = y * (rt->env.pitch / sizeof(unsigned int)) + x;
		rt->env.pixels[pixel_pos] = int_color;
	}
}

static	int				if_shadow(t_list *node_obj, t_inter *inter, t_list *node, t_ray *ray_obj)
{
	int					shadow;
	double				tmp;

	shadow = 0;
	while (node_obj)
	{
		if (((t_obj *)node_obj->content)->is_src != 1)
		{
			if(!isnan(tmp = ((t_obj *)node_obj->content)->inter(((t_obj *)node_obj->content), ray_obj)) && tmp > 0.01 && tmp <= length_vector3f(sub_vector3f(((t_obj *)node->content)->pos, inter->impact)) && diffuse_light(((t_obj *)node->content), inter) > 0)
			{
				shadow = 1;
				break;
			}
		}
		node_obj = node_obj->next;
	}
	return (shadow);
}

int			apply_light(t_rt *rt, t_ray *ray, t_vector3f *color, t_inter *inter, int test)
{
	int 				shadow;
	t_list				*save;
	float				coeffs;
	t_list				*node_obj;
	t_ray				ray_obj;
	float				tmp_dot;

	shadow = 0;
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
					tmp_dot = 2.0 * dot_vector3f(ray->dir, inter->normal);
					ray_obj.start = inter->impact;
					ray_obj.dir = sub_vector3f(ray->dir, mult_vector3f(inter->normal, tmp_dot));
					if (((t_plane *)inter->obj->data)->damier == 1)
					 	*color = add_vector3f(calcul_light_procedurale(inter, &coeffs, ((t_obj *)save->content)), *color);
					 else
					*color = add_vector3f(calcul_light(inter, &coeffs, ((t_obj *)save->content)), *color);
				if (test)
				{
					--test;
					*color = div_vector3f(
						mult_vector3f(
							add_vector3f(*color,
								get_inters(rt, &ray_obj, test)),
								LIGHT->intensity), 2);
				}
					cap_light(color);
				}
				shadow = 0;
			}
			save = save->next;
		}
	}
	return (test);
}

t_vector3f		get_inters(t_rt *rt, t_ray *ray, int rec)
{
	t_list				*node;
	t_inter				inter;
	t_vector3f			color;

	inter.obj = NULL;
	inter.distance = NAN;
	color = create_vector3f(0, 0, 0);
	node = rt->objs->head;
	while (node)
	{
		if (((t_obj *)node->content)->is_src != 1)
			calcul_inter(ray, ((t_obj *)node->content), &inter);
		node = node->next;
	}
	 rec = apply_light(rt, ray, &color, &inter, rec);
	return (color);
}

static void		render_pic(t_rt *rt)
{
	int			i;
	int			j;
	float		sample_x;
	float		sample_y;
	t_vector3f	color;
	t_ray		vp_point;
	t_vector2f	pixel;
	int 		rec = 5;

	j = 0;
	while (j < (rt->env.size.y + 1))
	{
		i = 0;
		while (i < (rt->env.size.x + 1))
		{
			sample_y = 1;
			while (sample_y <= rt->camera->sample)
			{
				sample_x = 1;
				while (sample_x <= rt->camera->sample)
				{
					pixel = create_vector2f((float)i + (1.0f / rt->camera->sample), (float)j + (1.0f / rt->camera->sample));
					vp_point.start = rt->camera->pos;
					vp_point.dir = get_viewplanepoint(rt->camera, &pixel);
					vp_point.dir = normalize_vector3f(sub_vector3f(vp_point.dir, vp_point.start));
					color = add_vector3f(color, get_inters(rt, &vp_point, rec));
					sample_x++;
				}
				sample_y++;
			}
			color = div_vector3f(color, rt->camera->sample * 2.0);
			cap_light(&color);
			put_in_image(rt, i, j, &color);
			++i;
		}
		++j;
	}
}

void			refresh_rt(t_rt *rt)
{
	Uint32	size_pic;

	SDL_QueryTexture(rt->env.text, &size_pic, NULL, &rt->env.wh[0], &rt->env.wh[1]);
	SDL_LockTexture(rt->env.text, NULL, (void**)&rt->env.pixels, &rt->env.pitch);
	render_pic(rt);
	SDL_UnlockTexture(rt->env.text);
}

void			render_rt(t_rt *rt)
{
	SDL_RenderClear(rt->env.rend);
	SDL_RenderCopy(rt->env.rend, rt->env.text, NULL, NULL);
	SDL_RenderPresent(rt->env.rend);
}

void			destroy_rt(t_rt *rt)
{
	if (rt)
	{
		rt->env.text ? SDL_DestroyTexture(rt->env.text) : 0;
		rt->env.rend ? SDL_DestroyRenderer(rt->env.rend) : 0;
		rt->env.win ? SDL_DestroyWindow(rt->env.win) : 0;
		SDL_Quit();
		rt->camera ? free(rt->camera) : 0;
		// free the data structure
	}
}

t_rt			*create_rt(int x, int y, char *name)
{
	t_rt		*rt;

	if (!(rt = ft_memalloc(sizeof(*rt))))
		return (ft_error("Failed to create main structure"));
	rt->env.size = create_vector2f(x, y);
	if (!parser(name, rt))
		return (NULL);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (ft_error("Failed to launch sdl"));
	rt->env.win = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			x, y,
			SDL_WINDOW_SHOWN);
	rt->env.rend = SDL_CreateRenderer(rt->env.win, -1, SDL_RENDERER_ACCELERATED);
	rt->env.text = SDL_CreateTexture(rt->env.rend, SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_STREAMING,
			x + 1, y + 1);
	if (!(rt->env.win && rt->env.text && rt->env.rend))
		return (ft_error("Failed to initialize sdl environment"));
	return (rt);
}
