/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3d2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 19:06:22 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/25 12:55:55 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_vector3d.h"

double			dot_vector3d(t_vector3d v1, t_vector3d v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector3d		cross_vector3d(t_vector3d v1, t_vector3d v2)
{
	t_vector3d	new;

	new.x = v1.y * v2.z - v1.z * v2.y;
	new.y = v1.z * v2.x - v1.x * v2.z;
	new.z = v1.x * v2.y - v1.y * v2.x;
	return (new);
}

t_vector3d		normalize_vector3d(t_vector3d v1)
{
	t_vector3d	new;
	float		inv_length;

	inv_length = 1.0f / length_vector3d(v1);
	new.x = v1.x * inv_length;
	new.y = v1.y * inv_length;
	new.z = v1.z * inv_length;
	return (new);
}

float			length_vector3d(t_vector3d v1)
{
	return (sqrtf(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z));
}
