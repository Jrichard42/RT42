/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:37:11 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/24 13:32:58 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "camera.h"
#include "parser.h"

int			create_camera(t_kvlexer *token, t_rt *rt)
{

	if (!(rt->camera = malloc(sizeof(t_camera))))
		return(-1);
	rt->camera->fov = get_as_float(token, "FOV");;
	rt->camera->up = create_vector3f(0.0, 1.0, 0.0);
	rt->camera->pos = get_as_vector3f(token, "POS");
	rt->camera->lookatpoint = get_as_vector3f(token, "LOOKAT");
	rt->camera->viewdir = normalize_vector3f(sub_vector3f(rt->camera->lookatpoint, rt->camera->pos)); // pas besoin de le recalculer
	/*rt->camera->u = cross_vector3f(rt->camera->viewdir, rt->camera->up); // pas besoin de le recalculer
	rt->camera->v = cross_vector3f(rt->camera->u, rt->camera->viewdir); // pas besoin de le recalculer
	rt->camera->u = normalize_vector3f(rt->camera->u); // pas besoin de le recalculer
	rt->camera->v = normalize_vector3f(rt->camera->v); // pas besoin de le recalculer
	rt->camera->vphalfwidth = tan(((rt->camera->fov / 2.0) * M_PI / 180.0)); // pas besoin de le recalculer
	rt->camera->aspectratio = (float)WIN_Y / (float)WIN_X;                                   // pas besoin de le recalculer
	rt->camera->vphalfheight = rt->camera->aspectratio * rt->camera->vphalfwidth; // pas besoin de le recalculer
	tmp = mult_vector3f(rt->camera->v, rt->camera->vphalfheight);
	rt->camera->vpbottomleftpoint = sub_vector3f(rt->camera->lookatpoint, tmp);
	tmp = mult_vector3f(rt->camera->u, rt->camera->vphalfwidth);
	rt->camera->vpbottomleftpoint = sub_vector3f(rt->camera->vpbottomleftpoint, tmp);
	rt->camera->x_inc_vec = rt->camera->u;
	rt->camera->n = rt->camera->vphalfwidth;
	tmp_f = 2.0f * rt->camera->n / (float)WIN_X;
	rt->camera->x_inc_vec = mult_vector3f(rt->camera->x_inc_vec, tmp_f);
	rt->camera->y_inc_vec = rt->camera->v;
	rt->camera->n = rt->camera->vphalfwidth;
	tmp_f = 2.0f * rt->camera->n / (float)WIN_Y;
	rt->camera->y_inc_vec = mult_vector3f(rt->camera->y_inc_vec, tmp_f);*/
	rt->camera->vphalfwidth = tanf((rt->camera->fov / 2) * M_PI / 180.0f);
	rt->camera->aspectratio= (float)WIN_Y / (float)WIN_X;
	rt->camera->vphalfheight = rt->camera->vphalfwidth * rt->camera->aspectratio;
	rt->camera->u = cross_vector3f(rt->camera->viewdir, rt->camera->up);
	rt->camera->v = cross_vector3f(rt->camera->u, rt->camera->viewdir);
	rt->camera->u = normalize_vector3f(rt->camera->u);
	rt->camera->v = normalize_vector3f(rt->camera->v);
	rt->camera->vpbottomleftpoint= sub_vector3f(rt->camera->lookatpoint, add_vector3f(
		mult_vector3f(rt->camera->u, rt->camera->vphalfwidth),
		mult_vector3f(rt->camera->v, rt->camera->vphalfheight)));
	rt->camera->y_inc_vec = mult_vector3f(
		rt->camera->v, (2.0f * rt->camera->vphalfheight) / (float)WIN_Y);
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
//camera->castray = sub_vector3f(camera->viewplanepoint, camera->pos);
//camera->castray = normalize_vector3f(camera->castray);
	return (camera->viewplanepoint);
}
