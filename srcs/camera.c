/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:37:11 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/18 19:37:09 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "camera.h"
#include "parser.h"

int				create_camera(t_kvlexer *token, t_rt *rt)
{
	t_camera	*camera;
	t_vector3f	up;
	t_vector3f	size;
	t_vector3f	view_dir;

	if (!(camera = ft_memalloc(sizeof(*camera))))
		return (-1);
	size = get_as_vector3f(token, "SIZE");
	view_dir= get_as_vector3f(token, "VIEW_DIR");
	up.x = 0.0f;
	up.y = -1.0f;
	up.z = 0.0f;
	camera->vhw = tan((camera->fov / 2) * M_PI / 180.0f);
	camera->aspect = size.y / size.x;
	camera->vhh = camera->vhw * camera->aspect;
	camera->vu = cross_vector3f(view_dir, up);
	camera->vv = cross_vector3f(camera->vu, view_dir);
	camera->vu = normalize_vector3f(camera->vu);
	camera->vv = normalize_vector3f(camera->vv);
	camera->vp = sub_vector3f(camera->lookatpoint, add_vector3f(
		mult_vector3f(camera->vu, camera->vhw),
		mult_vector3f(camera->vv, camera->vhh)));
	camera->viy = mult_vector3f(
		camera->vv, (2.0f * camera->vhh) / size.y);
	camera->vix = mult_vector3f(
	camera->vu, (2.0f * camera->vhw) / size.x);
	rt->camera = camera;
	return (0);
}

t_vector3f		get_viewplanepoint(t_camera *camera, t_vector2f *pixel)
{
	t_vector3f	v;
	t_vector3f	vpp;

	vpp = add_vector3f(camera->vp, add_vector3f(
		mult_vector3f(camera->vix, pixel->x),
		mult_vector3f(camera->viy, pixel->y)));
	v = sub_vector3f(vpp, camera->eyepoint);
	normalize_vector3f(v);
	return (v);
}
