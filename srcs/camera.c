/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bruit_perlin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 15:26:01 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/26 16:20:51 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "camera.h"
#include "parser.h"

void		fill_camera(t_rt *rt)
{
	rt->camera->viewdir = normalize_vector3f(sub_vector3f(rt->camera->
										lookatpoint, rt->camera->pos));
	rt->camera->vphalfwidth = tanf((rt->camera->fov / 2.0f) * M_PI / 180.0f);
	rt->camera->aspectratio = (double)WIN_Y / (double)WIN_X;
	rt->camera->vphalfheight = rt->camera->vphalfwidth
								* rt->camera->aspectratio;
	rt->camera->u = cross_vector3f(rt->camera->viewdir, rt->camera->up);
	rt->camera->v = cross_vector3f(rt->camera->u, rt->camera->viewdir);
	rt->camera->u = normalize_vector3f(rt->camera->u);
	rt->camera->v = normalize_vector3f(rt->camera->v);
	rt->camera->vpbottomleftpoint = sub_vector3f(rt->camera->lookatpoint,
		add_vector3f(mult_vector3f(rt->camera->u, rt->camera->vphalfwidth),
		mult_vector3f(rt->camera->v, rt->camera->vphalfheight)));
	rt->camera->y_inc_vec = mult_vector3f(
	rt->camera->v, (2.0f * rt->camera->vphalfheight) / (double)WIN_Y);
	rt->camera->x_inc_vec = mult_vector3f(
		rt->camera->u, (2.0f * rt->camera->vphalfwidth) / (double)WIN_X);
}

int			create_camera(t_kvlexer *token, t_rt *rt)
{
	if (!(rt->camera = malloc(sizeof(t_camera))))
		return (-1);
	if (!get_as_int(token, "FOV", &(rt->camera->fov)))
		return ((int)ft_error("The CAMERA should contain a field FOV"));
	rt->camera->up = create_vector3f(0.0, -1.0, 0.0);
	if (!get_as_vector3f(token, "POS", &(rt->camera->pos)))
		return ((int)ft_error("The CAMERA should contain a field POS"));
	if (!get_as_vector3f(token, "LOOKAT", &(rt->camera->lookatpoint)))
		return ((int)ft_error("The CAMERA should contain a field LOOKAT"));
	if (!get_as_int(token, "SAMPLING", &(rt->camera->sampling)))
		rt->camera->sampling = 1;
	if (rt->camera->sampling > 4)
	{
		ft_putstr("The sampling value has been resized to 4");
		rt->camera->sampling = 4;
	}
	if (rt->camera->sampling < 1)
	{
		ft_putstr("The sampling value has been resized to 1");
		rt->camera->sampling = 1;
	}
	fill_camera(rt);
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
