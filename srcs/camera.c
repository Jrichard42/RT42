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

/*int				create_camera(t_kvlexer *token, t_rt *rt)
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
  }*/
int        create_camera(t_kvlexer *token, t_rt *rt)
{
	t_camera	*camera;
	t_vector3f	forward;
	t_vector3f	side;
	t_vector3f	up;
	float		ratio;

	if (!(camera = ft_memalloc(sizeof(*camera))))
		return (-1);
	t_vector3f pos = get_as_vector3f(token, "POS");
	t_vector3f look_at = get_as_vector3f(token, "LOOKAT");
	float fov = get_as_float(token, "FOV");
	t_vector3f res = get_as_vector3f(token, "RES");
	printf("toto = %f, %f, %f\n", pos.x, pos.y, pos.z);

	camera->pos = pos;
	camera->look_at = look_at;
	camera->fov = fov;
	camera->res = res;

	ratio = res.y / res.x;
	
	camera->distance = length_vector3f(sub_vector3f(look_at, pos));
	printf("distance = %f\n", camera->distance);
	forward = normalize_vector3f(sub_vector3f(look_at, pos));
	printf("forward = %f  %f %f\n", forward.x, forward.y, forward.z);
	side = normalize_vector3f(cross_vector3f(forward, create_vector3f(0, 1, 0)));
	printf("side = %f  %f %f\n", side.x, side.y, side.z);
	up = normalize_vector3f(cross_vector3f(side, forward));
	printf("up = %f  %f %f\n", up.x, up.y, up.z);
	camera->size.x = tanf((fov / 2.0) * M_PI / 180.0) * 2.0 * camera->distance;
	camera->size.y = camera->size.x * ratio;
	printf("size = %f  %f\n", camera->size.x, camera->size.y);

	camera->top_left = mult_vector3f(up, camera->size.y / 2.0);
	camera->top_left = add_vector3f(mult_vector3f(side, camera->size.x / 2.0), camera->top_left);
	camera->top_left = add_vector3f(mult_vector3f(forward, camera->distance), camera->top_left);
	camera->top_left = add_vector3f(pos, camera->top_left);
	printf("camera->top_left = %f  %f  %f\n", camera->top_left.x, camera->top_left.y, camera->top_left.z);
	camera->up = up;
	camera->side = side;
	rt->camera = camera;
	return (0);
}

t_vector3f		get_viewplanepoint(t_camera *camera, t_vector2f *pixel)
{
	float	tmp_x;
	float	tmp_y;
	t_vector3f	plop;

	plop = camera->top_left;
	tmp_x = camera->size.x * (pixel->x / (camera->res.x - 1.0));
	tmp_y = camera->size.y * (pixel->y / (camera->res.y - 1.0));
	plop = sub_vector3f(plop, mult_vector3f(camera->side, tmp_x));
	plop = sub_vector3f(plop, mult_vector3f(camera->up, tmp_y));
	return (plop);
}
