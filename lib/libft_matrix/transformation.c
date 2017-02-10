/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 15:12:59 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/06 12:39:33 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_matrix.h"

t_matrix				rotation_x_matrix(t_matrix *transf, float angle)
{
	t_matrix	rotate;
	float		angle_rad;

	rotate = create_matrix();
	angle_rad = angle * M_PI / 180.0;
	(rotate.tab)[1][1] = cosf(angle_rad);
	(rotate.tab)[1][2] = -sinf(angle_rad);
	(rotate.tab)[2][1] = sinf(angle_rad);
	(rotate.tab)[2][2] = cosf(angle_rad);
	return (mult_matrix(&rotate, transf));
}

t_matrix				rotation_y_matrix(t_matrix *transf, float angle)
{
	t_matrix	rotate;
	float		angle_rad;

	rotate = create_matrix();
	angle_rad = angle * M_PI / 180.0;
	(rotate.tab)[0][0] = cosf(angle_rad);
	(rotate.tab)[0][2] = sinf(angle_rad);
	(rotate.tab)[2][0] = -sinf(angle_rad);
	(rotate.tab)[2][2] = cosf(angle_rad);
	return (mult_matrix(&rotate, transf));
}

t_matrix		rotation_z_matrix(t_matrix *transf, float angle)
{
	t_matrix	rotate;
	float		angle_rad;

	rotate = create_matrix();
	angle_rad = angle * M_PI / 180.0;
	(rotate.tab)[0][0] = cosf(angle_rad);
	(rotate.tab)[0][1] = -sinf(angle_rad);
	(rotate.tab)[1][0] = sinf(angle_rad);
	(rotate.tab)[1][1] = cosf(angle_rad);
	return (mult_matrix(&rotate, transf));
}

t_matrix		scale_matrix(t_matrix *transf, t_vector3f vector)
{
	t_matrix	scale;

	scale = create_matrix();
	(scale.tab)[0][0] = vector.x;
	(scale.tab)[1][1] = vector.y;
	(scale.tab)[2][2] = vector.z;
	return (mult_matrix(&scale, transf));
}

t_matrix		translation_matrix(t_matrix *transf, t_vector3f vector)
{
	t_matrix	translate;

	translate = create_matrix();
	(translate.tab)[0][3] = vector.x;
	(translate.tab)[1][3] = vector.y;
	(translate.tab)[2][3] = vector.z;
	return (mult_matrix(&translate, transf));
}
