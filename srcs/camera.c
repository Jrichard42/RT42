/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:37:11 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/17 19:38:05 by dbreton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "camera.h"

static void		cam_vector_compute(t_camera *camera, t_vector2f *size, t_vector3f view_dir)
{
	t_vector3f    up;

	up.x = 0.0f;
	up.y = -1.0f;
	up.z = 0.0f;
	camera->vhw = tan((camera->fov / 2) * M_PI / 180.0f);
	camera->aspect = (double)size->y / (double)size->x;
	camera->vhh = camera->vhw * camera->aspect;
	camera->vu = cross_vector3f(view_dir, up);
	camera->vv = cross_vector3f(camera->vu, view_dir);
	camera->vu = normalize_vector3f(camera->vu);
	camera->vv = normalize_vector3f(camera->vv);
	camera->vp = sub_vector3f(s->cam.lp, add_vector3f(
		mult_vector3f(camera->vu, camera->vhw),
		mult_vector3f(camera->vv, camera->vhh)));
	camera->viy = mult_vector3f(
		camera->vv, (2.0f * camera->vhh) / (double)size->y);
	camera->vix = mult_vector3f(
	camera->vu, (2.0f * camera->vhw) / (double)size->x);
}

t_vector3f	get_viewplanepoint(t_camera *camera, int x, int y)// nom des fonction a changer
{
	t_vector3f	v;
	t_vector3f	vpp;
	vpp = add_vector3f(camera->vp, add_vector3f(
		mult_vector3f(camera->vix, (double)x),
		mult_vector3f(camera->viy, (double)y)));
	v = sub_vector3f(vpp, camera->eyepoint);
	normalize_vector(&v);
	return (v);
}
