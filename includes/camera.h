/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:20:46 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/17 19:11:43 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "rt.h"
# include "ft_kvlexer.h"
# include "libft_matrix.h"

typedef	struct	s_camera 
{
	t_vector3f	eyepoint;
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

void			create_camera(t_kvlexer *token, t_rt *rt);	// initialise la camera
t_vector3f		get_viewplanepoint(t_camera *, t_vector2f *); // point 2d (pixel) a point 3d (viewplane || le monde)

#endif
