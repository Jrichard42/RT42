/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreton <dbreton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/19 19:15:07 by dbreton           #+#    #+#             */
/*   Updated: 2017/02/20 14:35:37 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "light.h"
#include "obj.h"
#include "inter.h"
#include "ray.h"
#include "parser.h"	

int                get_color_value(t_vector3f c)
{
    int            res;

    res = (unsigned char)(c.x) & 0xFF;
    res += ((unsigned char)(c.y) & 0x00FF) << 8;
    res += ((unsigned char)(c.z) & 0x0000FF) << 16;
    return (res);
}

static void			calcul_inter(t_ray *ray, t_obj *obj, t_inter *inter)
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
	float				tmp;

	shadow = 0;
	while (node_obj)
	{
		if (((t_obj *)node_obj->content)->is_src != 1)
		{
			if(!isnan(tmp = ((t_obj *)node_obj->content)
				->inter(((t_obj *)node_obj->content), ray_obj))
				&& tmp > 0.01 && tmp <
				length_vector3f(sub_vector3f(((t_obj *)node->content)->pos
					, inter->impact)) && diffuse_light(((t_obj *)node->content)
				, inter) > 0)
			{
				shadow = 1;
				break;
			}
		}
		node_obj = node_obj->next;
	}
	return (shadow);
}

static	void			apply_light(t_list *node, t_ray *ray, t_vector3f *color, t_inter *inter)
{
	int 				shadow;
	t_list				*save;
	t_list				*node_obj;
	t_ray				ray_obj;

	shadow = 0;
	save = node;
	if (inter->obj != NULL)
	{
		while (node)
		{
			if (((t_obj *)node->content)->is_src == 1)
			{
				node_obj = save;
				ray_obj.start = inter->impact;
				ray_obj.dir = normalize_vector3f(sub_vector3f(((t_obj *)node->content)->pos, inter->impact));
				shadow = if_shadow(node_obj, inter, node, &ray_obj);
				if (shadow != 1)
					*color = calcul_light(((t_obj *)node->content), inter, ray, color);
				shadow = 0;
			}
			node = node->next;
		}
	}
}

static t_vector3f		get_inters(t_rt *rt, t_vector3f *vp_point)
{
	t_list				*node;
	t_inter				inter;
	t_vector3f			color;
	t_ray				ray;

	inter.obj = NULL;
	inter.distance = NAN;
	color = create_vector3f(0, 0, 0);
	node = rt->objs->head;
	while (node)
	{
		ray.start = rt->camera->pos; //eyepoint
		ray.dir = normalize_vector3f(sub_vector3f(*vp_point, ray.start));
		if (((t_obj *)node->content)->is_src != 1)
			calcul_inter(&ray, ((t_obj *)node->content), &inter);
		node = node->next;
	}
	node = rt->objs->head;
	apply_light(node, &ray, &color, &inter);
	return (color);
}

static void		render_pic(t_rt *rt)
{
	int			i;
	int			j;
	t_vector3f	color;
	t_vector3f	vp_point;
	t_vector2f	pixel;

	j = 0;
	while (j < (rt->env.size.y + 1))
	{
		i = 0;
		while (i < (rt->env.size.x + 1))
		{
			pixel = create_vector2f(i, j);
			vp_point = get_viewplanepoint(rt->camera, &pixel);
			//printf("x = %f y = %f z = %f\n",vp_point.x, vp_point.y, vp_point.z );
			color = get_inters(rt, &vp_point);
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

t_rt			*create_rt(int x, int y, char *name)
{
	t_rt		*rt;

	if (!(rt = ft_memalloc(sizeof(*rt))))
		return (NULL);  //TODO check
	rt->env.size.x = x;
	rt->env.size.y = y;
	if (parser(name, rt) == -1)
		return (NULL);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		exit (-1);
		//ft_exit(3, "sdl init failed"); // check
	}
	rt->env.win = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			x, y,
			SDL_WINDOW_SHOWN);
	rt->env.rend = SDL_CreateRenderer(rt->env.win, -1, SDL_RENDERER_ACCELERATED);
	rt->env.text = SDL_CreateTexture(rt->env.rend, SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_STREAMING,
			x + 1, y + 1);
	if (!(rt->env.win && rt->env.text && rt->env.rend))
	{	
		exit(-1);
		//ft_exit(3, "renderer init failed"); // check
	}
	return (rt);
}
