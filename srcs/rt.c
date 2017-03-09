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
#include "thread_manager.h"

#define	LIGHT ((t_light *)((t_obj *)save->content)->data)
#define T_DATA ((t_thread_data *)data)
//TODO put in .h
t_vector3f		get_inters(t_rt *rt, t_ray *ray);
// #include "parser.h"
// #include "opencl.h"

int                get_color_value(t_vector3f c)
{
	int            res;

	res = (unsigned char)(c.x) & 0xFF;
	res += ((unsigned char)(c.y) & 0x00FF) << 8;
	res += ((unsigned char)(c.z) & 0x0000FF) << 16;
	return (res);
}

void			calcul_inter(t_cl *cl, t_ray *ray, t_obj *obj, t_inter *inter)
{
	float 			tmp;

	tmp = obj->inter(obj, ray);
	if (!isnan(tmp) && tmp > 0.01 && (tmp < inter->distance || isnan(inter->distance)))
	{
		inter->distance = tmp;
		// inter->impact = add_vector3f_cl(cl, ray->start, mult_vector3f(ray->dir, inter->distance));
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
			if(!isnan(tmp = ((t_obj *)node_obj->content)->inter(((t_obj *)node_obj->content), ray_obj)) && tmp > 0.01 && tmp < length_vector3f(sub_vector3f(((t_obj *)node->content)->pos, inter->impact)))
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

void		apply_light(t_rt *rt, t_ray *ray, t_vector3f *color, t_inter *inter)
{
	int 				shadow;
	t_list				*save;
	float				coeffs;
	t_list				*node_obj;
	t_ray				ray_obj;

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
					*color = add_vector3f(calcul_light(inter, &coeffs, ((t_obj *)save->content)), *color);
					cap_light(color);
				}
				shadow = 0;
			}
			save = save->next;
		}
	}
}

t_vector3f		get_inters(t_rt *rt, t_ray *ray)
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
			calcul_inter(rt->cl, ray, ((t_obj *)node->content), &inter);
		node = node->next;
	}
	apply_light(rt, ray, &color, &inter);
	return (color);
}

void			*render_chunk(void *data)
{
	t_vector2f	pixel;
	t_vector3f  color;
	t_ray       vp_point;

	pixel = create_vector2f(T_DATA->index % WIN_X, T_DATA->index / WIN_X);
	while (T_DATA->size > 0)
	{
		if (pixel.x == WIN_X)
		{
			pixel.x = 0;
			++pixel.y;
		}
		vp_point.start = T_DATA->rt->camera->pos;
		vp_point.dir = get_viewplanepoint(T_DATA->rt->camera, &pixel);
		vp_point.dir = normalize_vector3f(sub_vector3f(vp_point.dir, vp_point.start));
		color = get_inters(T_DATA->rt, &vp_point);
		put_in_image(T_DATA->rt, pixel.x, pixel.y, &color);
		++pixel.x;
		--T_DATA->size;
	}
	return (NULL);
}

void			refresh_rt(t_rt *rt)
{
	Uint32	size_pic;

	SDL_QueryTexture(rt->env.text, &size_pic, NULL, &rt->env.wh[0], &rt->env.wh[1]);
	SDL_LockTexture(rt->env.text, NULL, (void**)&rt->env.pixels, &rt->env.pitch);
	thread_manager(rt);
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

