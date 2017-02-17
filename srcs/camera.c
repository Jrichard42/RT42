/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:37:11 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/17 19:18:18 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "camera.h"

static void		cam_vector_compute(t_camera *camera, t_vector2f *size, t_vector3f view_dir)
{
	t_vector3f	up;

	up.x = 0.0f;
	up.y = -1.0f;
	up.z = 0.0f;
	camera->vhw = tan((camera->fov / 2) * M_PI / 180.0f);
	camera->aspect = (double)size->y / (double)size->x;
	camera->vhh = camera->vhw * camera->aspect;
	camera->vu = mult_vec_by_vec(view_dir, up);
	camera->vv = mult_vec_by_vec(s->cam.vu, view_dir);
	normalize_vector3f(&s->cam.vu);
	normalize_vector3f(&s->cam.vv);
	camera->vp = sub_vec_by_vec(s->cam.lp, add_vector(
		mult_vec_double(camera->vu, camera->vhw),
		mult_vec_double(camera->vv, camera->vhh)));
	camera->viy = mult_vec_double(
		camera->vv, (2.0f * camera->vhh) / (double)size->y);
	camera->vix = mult_vec_double(
	camera->vu, (2.0f * camera->vhw) / (double)size->x);
}

t_camera		create_camera()
{

}

t_vector3f		get_viewplanepoint(t_camera *camera, int x, int y)// nom des fonction a changer
{
	t_vector3f	v;
	t_vector3f	vpp;
	vpp = add_vector3f(camera->vp, add_vector3f(
		mult_vec_double(camera->vix, (double)x),
		mult_vec_double(camera->viy, (double)y)));
	v = sub_vector3f(vpp, camera->c);
	normalize_vector(&v);
	return (v);
}
