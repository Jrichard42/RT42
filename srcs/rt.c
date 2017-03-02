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
#include "opencl.h"

t_vector3f			add_vector3f_cl(t_cl *cl, t_vector3f v1, t_vector3f v2)
{
	float 			v[3][3];
	cl_mem 			memobj[3];
	t_vector3f		res;
	cl_kernel 		kernel;

	v[0][0] = v1.x;
	v[0][1] = v1.y;
	v[0][2] = v1.z;
	v[1][0] = v2.x;
	v[1][1] = v2.y;
	v[1][2] = v2.z;
	kernel = ht_get(cl->kernels, "add_vector3f");
	memobj[0] = clCreateBuffer(cl->env->ctx, CL_MEM_READ_WRITE, 3 * sizeof(float), NULL, NULL);
	memobj[1] = clCreateBuffer(cl->env->ctx, CL_MEM_READ_WRITE, 3 * sizeof(float), NULL, NULL);
	memobj[2] = clCreateBuffer(cl->env->ctx, CL_MEM_READ_WRITE, 3 * sizeof(float), NULL, NULL);
	clEnqueueWriteBuffer(cl->queue, memobj[0], CL_TRUE, 0, 3*sizeof(float), v[0], 0, NULL, NULL);
	clEnqueueWriteBuffer(cl->queue, memobj[1], CL_TRUE, 0, 3*sizeof(float), v[1], 0, NULL, NULL);
	clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj[0]);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&memobj[1]);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&memobj[2]);
	clEnqueueTask(cl->queue, kernel, 0, NULL, NULL);
	clEnqueueReadBuffer(cl->queue, memobj[2], CL_TRUE, 0, 3 * sizeof(float), (void *)&v[2], 0, NULL, NULL);
	res.x = v[2][0];
	res.y = v[2][1];
	res.z = v[2][2];
	clReleaseMemObject(memobj[0]);
	clReleaseMemObject(memobj[1]);
	clReleaseMemObject(memobj[2]);
	return (res);
}

int                get_color_value(t_vector3f c)
{
    int            res;

    res = (unsigned char)(c.x) & 0xFF;
    res += ((unsigned char)(c.y) & 0x00FF) << 8;
    res += ((unsigned char)(c.z) & 0x0000FF) << 16;
    return (res);
}

static void			calcul_inter(t_cl *cl, t_ray *ray, t_obj *obj, t_inter *inter)
{
	float 			tmp;

	tmp = obj->inter(obj, ray);
	if (!isnan(tmp) && tmp > 0.01 && (tmp < inter->distance || isnan(inter->distance)))
	{
		inter->distance = tmp;
		inter->impact = add_vector3f_cl(cl, ray->start, mult_vector3f(ray->dir, inter->distance));
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
			calcul_inter(rt->cl, &ray, ((t_obj *)node->content), &inter);
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
