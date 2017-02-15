/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:37:11 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/15 17:43:59 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static void      cam_vector_compute(t_camera *camera, t_vector2f *size, t_vector3f view_dir)
{
	t_vector3f    up;
	up.x = 0.0f;
	up.y = -1.0f;
	up.z = 0.0f;
	camera->vhw = tan((camera->fov / 2) * M_PI / 180.0f);
	camera->aspect = (double)size->y / (double)size->x;
	camera->vhh = camera->vhw * camera->aspect;
	camera->vu = mult_vec_by_vec(view_dir, up);
	camera->vv = mult_vec_by_vec(s->cam.vu, view_dir);
	normalize_vector(&s->cam.vu);
	normalize_vector(&s->cam.vv);
	camera->vp = sub_vec_by_vec(s->cam.lp, add_vector(
		mult_vec_double(camera->vu, camera->vhw),
		mult_vec_double(camera->vv, camera->vhh)));
	camera->viy = mult_vec_double(
		camera->vv, (2.0f * camera->vhh) / (double)size->y);
	camera->vix = mult_vec_double(
	camera->vu, (2.0f * camera->vhw) / (double)size->x);
}

void        render_pic(t_rt *rt)
{
	int        i;
	int        j;
	t_color      tmp;
	t_vector3f    v;

	j = 0;
	while (j < (size->y + 1))
	{
		i = 0;
		while (i < (size->x + 1))
		{
			v = get_viewplanepoint(rt->camera, i, j);
			tmp = get_inters(s, &v);// a changer
			put_in_image(s, i, j, tmp);// a changer
			++i;
		}
		++j;
	}
}


t_camera	create_camera()
{

}

t_vector3f	get_viewplanepoint(t_camera *camera, int x, int y)// nom des fonction a changer
{
	t_vector3f    v;
	t_vector3f    vpp;
	vpp = add_vector3f(camera->vp, add_vector3f(
		mult_vec_double(camera->vix, (double)x),
		mult_vec_double(camera->viy, (double)y)));
	v = sub_vector3f(vpp, camera->c);
	normalize_vector(&v);
	return (v);
}
