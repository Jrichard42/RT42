/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:37:11 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/21 13:50:49 by hpachy           ###   ########.fr       */
/*   Updated: 2017/02/25 14:32:08 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "camera.h"
#include "parser.h"

int			create_camera(t_kvlexer *token, t_rt *rt)
{

	if (!(rt->camera = malloc(sizeof(t_camera))))
		return(-1);
	rt->camera->sample = get_as_float(token, "ANTI_ALIAZING");
	rt->camera->fov = get_as_float(token, "FOV");;
	rt->camera->up = create_vector3f(0.0, -1.0, 0.0);
	rt->camera->pos = get_as_vector3f(token, "POS");
	rt->camera->lookatpoint = get_as_vector3f(token, "LOOKAT");
	rt->camera->viewdir = normalize_vector3f(sub_vector3f(rt->camera->lookatpoint, rt->camera->pos)); // pas besoin de le recalculer
	rt->camera->vphalfwidth = tanf((rt->camera->fov / 2.0f) * M_PI / 180.0f);
	rt->camera->aspectratio= (double)WIN_Y / (double)WIN_X;
	rt->camera->vphalfheight = rt->camera->vphalfwidth * rt->camera->aspectratio;
	rt->camera->u = cross_vector3f(rt->camera->viewdir, rt->camera->up);
	rt->camera->v = cross_vector3f(rt->camera->u, rt->camera->viewdir);
	rt->camera->u = normalize_vector3f(rt->camera->u);
	rt->camera->v = normalize_vector3f(rt->camera->v);
	rt->camera->vpbottomleftpoint= sub_vector3f(rt->camera->lookatpoint, add_vector3f(
		mult_vector3f(rt->camera->u, rt->camera->vphalfwidth),
		mult_vector3f(rt->camera->v, rt->camera->vphalfheight)));
	rt->camera->y_inc_vec = mult_vector3f(
	rt->camera->v, (2.0f * rt->camera->vphalfheight) / (double)WIN_Y);

	rt->camera->x_inc_vec = mult_vector3f(
		rt->camera->u, (2.0f * rt->camera->vphalfwidth) / (float)WIN_X);
	return (1);
}

t_vector3f	get_viewplanepoint(t_camera *camera, t_vector2f *pixel)
{
	t_vector3f		tmp;

	tmp = add_vector3f(
		mult_vector3f(camera->x_inc_vec, pixel->x),
		mult_vector3f(camera->y_inc_vec, pixel->y));
	camera->viewplanepoint = add_vector3f(camera->vpbottomleftpoint, tmp);
	return (camera->viewplanepoint);
}
