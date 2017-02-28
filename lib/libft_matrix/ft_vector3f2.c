/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3f2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 19:08:04 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/25 12:55:09 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_vector3f.h"

float			dot_vector3f(t_vector3f v1, t_vector3f v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector3f		cross_vector3f(t_vector3f v1, t_vector3f v2)
{
	t_vector3f	new;

	new.x = v1.y * v2.z - v1.z * v2.y;
	new.y = v1.z * v2.x - v1.x * v2.z;
	new.z = v1.x * v2.y - v1.y * v2.x;
	return (new);
}

t_vector3f		normalize_vector3f(t_vector3f v1)
{
	t_vector3f	new;
	float		inv_length;

	inv_length = 1.0f / length_vector3f(v1);
	new.x = v1.x * inv_length;
	new.y = v1.y * inv_length;
	new.z = v1.z * inv_length;
	return (new);
}

float			length_vector3f(t_vector3f v1)
{
	return (sqrtf(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z));
}

t_vector3f		transform_vector3f(t_vector3f v1, t_matrix *transf)
{
	t_vector3f	new;

	new = create_vector3f(0, 0, 0);
	new.x = transf->tab[0][0] * v1.x + transf->tab[0][1] * v1.y +
		transf->tab[0][2] * v1.z + transf->tab[0][3];
	new.y = transf->tab[1][0] * v1.x + transf->tab[1][1] * v1.y +
		transf->tab[1][2] * v1.z + transf->tab[1][3];
	new.z = transf->tab[2][0] * v1.x + transf->tab[2][1] * v1.y +
		transf->tab[2][2] * v1.z + transf->tab[2][3];
	return (new);
}
