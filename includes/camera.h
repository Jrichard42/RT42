/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:20:46 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/21 13:49:51 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "ft_kvlexer.h"
# include "libft_matrix.h"
# define WIN_X 1300
# define WIN_Y 1300

typedef struct s_rt t_rt;

typedef	struct	s_camera 
{
	t_vector3f	pos;
	t_vector3f	lookatpoint;
	t_vector3f	up;
	t_vector3f	light;
	t_vector3f	viewdir;
	t_vector3f	u;
	t_vector3f	v;
	t_vector3f	vpbottomleftpoint;
	t_vector3f	viewplanepoint;
	t_vector3f	castray;
	t_vector3f	x_inc_vec;
	t_vector3f	y_inc_vec;
	float		vphalfwidth;
	float		vphalfheight;
	int			fov;
	float		aspectratio;
	float		n;
}				t_camera;
// typedef struct	s_camera
// {
// 	t_vector3f	pos;
// 	t_vector3f	size;
// 	t_vector3f	look_at;
// 	t_vector3f	up;
// 	t_vector3f	side;
// 	t_vector3f	res;
// 	t_vector3f	top_left;
// 	float		distance;
// 	float		fov;
// }				t_camera;

int					create_camera(t_kvlexer *token, t_rt *rt);
t_vector3f			get_viewplanepoint(t_camera *camera, t_vector2f *pixel);

#endif
