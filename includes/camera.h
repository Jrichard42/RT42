/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:20:46 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/18 19:57:14 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "ft_kvlexer.h"
# include "libft_matrix.h"

typedef struct s_rt t_rt;

/*typedef	struct	s_camera 
{
	t_vector3f	eyepoint;
	t_vector3f	lookatpoint;
	t_vector3f	up;
	t_vector3f	light;
	t_vector3f	viewdir;
	t_vector3f	vu;
	t_vector3f	vv;
	t_vector3f	vp;
	t_vector3f	viewplanepoint;
	t_vector3f	castray;
	t_vector3f	vix;
	t_vector3f	viy;
	float		vhw;
	float		vhh;
	int			fov;
	float		aspect;
	float		n;
}				t_camera;*/

typedef struct	s_camera
{
	t_vector3f	pos;
	t_vector2f	size;
	t_vector3f	look_at;
	t_vector3f	up;
	t_vector3f	side;
	t_vector3f	res;
	t_vector3f	top_left;
	float		distance;
	float		fov;
}				t_camera;

int				create_camera(t_kvlexer *token, t_rt *rt);
t_vector3f		get_viewplanepoint(t_camera *camera, t_vector2f *pixel);

#endif
