/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreton <dbreton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/19 19:15:07 by dbreton           #+#    #+#             */
/*   Updated: 2017/02/17 19:04:08 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			calcul_inter(t_ray *ray, t_obj *obj, t_inter *inter)
{
	static	float		dist = nan;
	float 				tmp;

	tmp = obj->inter(obj, ray);
	if (dist == nan)
		dist = tmp;
	if (tmp != nan && tmp < dist && tmp > 0.01)
	{
		inter->impact = add_vector3f(ray->start, mult_vector3f(ray->dir, inter->distance));
		inter->normal = obj->normal(obj, &inter->impact);
		inter->distance = tmp;
		inter->obj = obj;
		dist = tmp;
	}
}

static void				put_in_image(t_rt *rt, int x, int y, t_color *color)
{
	unsigned int		pixel_pos;

	if ((x < rt->env.wh[0]) && y < (rt->env.wh[1]))
	{
		pixel_pos = y * (rt->env.pitch / sizeof(unsigned int)) + x;
		rt->env.pixels[pixel_pos] = get_color_value(color);
	}
}

static t_vector3f		get_inters(t_rt *rt, t_vector3f *vp_point)
{
	t_list				*node;
	t_inter				inter;
	t_vector3f			color;
	t_ray				ray;

	inter.obj = NULL;
	color = create_vector3f(0, 0, 0);
	node = rt->objs->head;
	while (node)
	{
		ray.start = rt->camera.eyepoint;
		ray.dir = normalize_vector3f(sub_vector3f(*vp_point, ray.start));
		if (((t_obj *)node->content)->is_src != 1)
			calcul_inter(&ray, ((t_obj *)node->content), &inter);
		node = node->next;
	}





	node = rt->objs->head;
	if (inter.obj != NULL)
	while (node)
	{
		if (((t_obj *)node->content)->is_src == 1)
			color = calcul_light(((t_obj *)node->content), &inter, &ray, color);
		node = node->next;
	}
	return (color);
}

static void		render_pic(t_rt *rt)
{
	int			i;
	int			j;
	t_color		color;
	t_vector3f	vp_point;
	t_vector2f	pixel;

	j = 0;
	while (j < (rt->env.size.y + 1))
	{
		i = 0;
		while (i < (rt->env.size.x + 1))
		{
			pixel = create_vector2f(i, j);
			vp_point = get_viewplanepoint(rt->camera, pixel);
			color = get_inters(rt, &vp_point);
			put_in_image(s, i, j, tmp);// a changer
			++i;
		}
		++j;
	}
}

void			refresh_rt(t_rt *rt)
{
		SDL_QueryTexture(rt.env->win, &rt.env->size, NULL, &rt.env->wh[0], &rt.env->wh[1]);
		SDL_LockTexture(rt.env->text, NULL, (void**)&rt.env->pixels, &rt.env->pitch);
		render_pic(rt);
		SDL_UnlockTexture(rt.env->text);
}

void			render_rt(t_rt *rt)
{
		SDL_RenderClear(rt->env->rend);
		SDL_RenderCopy(rt->env->rend, rt->env->text, NULL, NULL);
		SDL_RenderPresent(rt->env->rend);
}

t_rt			*create_rt(int x, int y, char *name)
{
	t_rt		*rt;

	if (!(rt = ft_memalloc(sizeof(*rt))))
		exit(1);  //TODO check
	rt->env.size.x = 1300;
	rt->env.size.y = 1300;
	if (parser(name, rt) == -1) // fonction parser TODO
		return (-1);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ft_exit(3, "sdl init failed"); // check
	rt->env->win = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			x, y,
			SDL_WINDOW_SHOWN); //check defines
	rt->env->rend = SDL_CreateRenderer(rt->env->win, -1, SDL_RENDERER_ACCELERATED);
	rt->env->win = SDL_CreateTexture(rt->env->rend, SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_STREAMING,
			x + 1, y + 1); //check_defines
	if (!(rt->env->win && rt->env->text && rt->env->rend))
		ft_exit(3, "renderer init failed"); // check
	return (rt);
}
