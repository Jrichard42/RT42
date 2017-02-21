/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:37:11 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/20 14:38:37 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "camera.h"
#include "parser.h"

int			create_camera(t_kvlexer *token, t_rt *rt)
{
	(void)token;
	if (!(rt->camera = malloc(sizeof(t_camera))))
		return(-1);
	rt->camera->fov = 120;
	rt->camera->up = create_vector3f(0.0, 1.0, 0.0);
	rt->camera->pos = create_vector3f(0.0, 0.0, 0.0);
	rt->camera->lookatpoint = create_vector3f(0.0, 0.0, 1.0);
	rt->camera->viewdir = sub_vector3f(rt->camera->lookatpoint, rt->camera->pos); // pas besoin de le recalculer
	rt->camera->u = cross_vector3f(rt->camera->viewdir, rt->camera->up); // pas besoin de le recalculer
	rt->camera->v = cross_vector3f(rt->camera->u, rt->camera->viewdir); // pas besoin de le recalculer
	rt->camera->u = normalize_vector3f(rt->camera->u); // pas besoin de le recalculer
	rt->camera->v = normalize_vector3f(rt->camera->v); // pas besoin de le recalculer
	rt->camera->vphalfwidth = tan(((rt->camera->fov / 2) * M_PI / 180.0)); // pas besoin de le recalculer
	rt->camera->aspectratio = WIN_Y / WIN_X;                                   // pas besoin de le recalculer
	rt->camera->vphalfheight = rt->camera->aspectratio * rt->camera->vphalfwidth; // pas besoin de le recalculer
	return (1);
}

t_vector3f	get_viewplanepoint(t_camera *camera, t_vector2f *pixel)
{
	t_vector3f		tmp;

	tmp = mult_vector3f(camera->v, camera->vphalfheight);
	camera->vpbottomleftpoint = sub_vector3f(camera->lookatpoint, tmp);
	tmp = mult_vector3f(camera->u, camera->vphalfwidth);
	camera->vpbottomleftpoint = sub_vector3f(camera->vpbottomleftpoint, tmp);
	camera->x_inc_vec = camera->u;
	camera->n = camera->vphalfwidth;
	camera->x_inc_vec = mult_vector3f(camera->x_inc_vec, camera->n);
	camera->x_inc_vec = mult_vector3f(camera->x_inc_vec, 2.0);
	camera->x_inc_vec = div_vector3f(camera->x_inc_vec, WIN_X);
	camera->v = camera->y_inc_vec;
	camera->n = camera->vphalfwidth;
	camera->y_inc_vec = mult_vector3f(camera->y_inc_vec, camera->n);
	camera->y_inc_vec = mult_vector3f(camera->y_inc_vec, 2.0);
	camera->y_inc_vec = div_vector3f(camera->y_inc_vec, WIN_Y);
	tmp = mult_vector3f(camera->x_inc_vec, pixel->x);
	camera->viewplanepoint = add_vector3f(camera->vpbottomleftpoint, tmp);
	tmp = mult_vector3f(camera->y_inc_vec, pixel->y);
	camera->viewplanepoint = add_vector3f(camera->viewplanepoint, tmp);
	camera->castray = sub_vector3f(camera->viewplanepoint, camera->pos);
	camera->castray = normalize_vector3f(camera->castray);
	return (camera->viewplanepoint);
}
