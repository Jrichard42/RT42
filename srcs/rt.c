/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreton <dbreton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/19 19:15:07 by dbreton           #+#    #+#             */
/*   Updated: 2017/02/25 11:14:20 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "light.h"
#include "obj.h"
#include "inter.h"
#include "ray.h"
#include "parser.h"	
#include "camera.h"

int             	   get_color_value(t_vector3f c)
{
	int            		res;

	res = (unsigned char)(c.x) & 0xFF;
	res += ((unsigned char)(c.y) & 0x00FF) << 8;
	res += ((unsigned char)(c.z) & 0x0000FF) << 16;
	return (res);
}

static void				calcul_inter(t_ray *ray, t_obj *obj, t_inter *inter)
{
	float 				tmp;

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
	if ((x < WIN_X) && y < WIN_Y)
	{
		pixel_pos = y * (rt->env.pitch / sizeof(unsigned int)) + x;
		rt->env.pixels[pixel_pos] = int_color;
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
	if (inter.obj != NULL)
	{
		while (node)
		{
			if (((t_obj *)node->content)->is_src == 1)
				color = calcul_light(((t_obj *)node->content), &inter, &ray, &color);
			node = node->next;
		}
	}
	return (color);
}

static void			calc_line(void *data)
{
	t_vector3f		color;
	t_vector3f		vp_point;
	t_vector2f		pixel;
	t_rt			*rt;

	pixel = create_vector2f(0, ((t_thread_data *)data)->line);
	rt = ((t_thread_data *)data)->rt;
	SDL_LockTexture(rt->env.text, NULL, (void**)&rt->env.pixels, &rt->env.pitch);
	while (pixel.x < rt->env.size.x)
	{
		vp_point = get_viewplanepoint(rt->camera, &pixel);
		color = get_inters(rt, &vp_point);
		put_in_image(rt, pixel.x, pixel.y, &color);
		++pixel.x;
	}
}

void				refresh_rt(t_rt *rt, t_thpool *pool)
{
	int				j;
	t_thread_data	thread_data;
	
	j = 0;
	thread_data.rt = rt;
	while (j < rt->env.size.y)
	{
		thread_data.line = j;
		push_job(pool, &calc_line, &thread_data, sizeof(t_thread_data));
		++j;
	}
}

void				render_rt(t_rt *rt)
{
	SDL_UnlockTexture(rt->env.text);
	SDL_RenderCopy(rt->env.rend, rt->env.text, NULL, NULL);
	SDL_RenderPresent(rt->env.rend);
}

t_rt				*create_rt(int x, int y, char *name)
{
	t_rt			*rt;

	if (!(rt = ft_memalloc(sizeof(*rt))))
		return (NULL);  //TODO check
	rt->env.size.x = x;
	rt->env.size.y = y;
	if (parser(name, rt) == -1)
		return (NULL);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		exit (-1); // TODO check
	rt->env.win = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			x, y,
			SDL_WINDOW_SHOWN);
	rt->env.rend = SDL_CreateRenderer(rt->env.win, -1, SDL_RENDERER_ACCELERATED);
	rt->env.text = SDL_CreateTexture(rt->env.rend, SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_STREAMING,
			x + 1, y + 1);
	if (!(rt->env.win && rt->env.text && rt->env.rend))
		exit(-1); // TODO check
	return (rt);
}
