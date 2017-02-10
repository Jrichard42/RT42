/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <jrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 14:31:42 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/12 19:25:39 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_vector3d.h"

t_vector3d		create_vector3d(double x, double y, double z)
{
	t_vector3d	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_vector3d		add_vector3d(t_vector3d v1, t_vector3d v2)
{
	t_vector3d	new;

	new.x = v1.x + v2.x;
	new.y = v1.y + v2.y;
	new.z = v1.z + v2.z;
	return (new);
}

t_vector3d		sub_vector3d(t_vector3d v1, t_vector3d v2)
{
	t_vector3d	new;

	new.x = v1.x - v2.x;
	new.y = v1.y - v2.y;
	new.z = v1.z - v2.z;
	return (new);
}

t_vector3d		mult_vector3d(t_vector3d v1, float nb)
{
	t_vector3d  new;

	new.x = v1.x * nb;
	new.y = v1.y * nb;
	new.z = v1.z * nb;
	return (new);
}

t_vector3d		div_vector3d(t_vector3d v1, float nb)
{
	t_vector3d  new;

	new.x = v1.x / nb;
	new.y = v1.y / nb;
	new.z = v1.z / nb;
	return (new);
}

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
	float		length;

	length = length_vector3d(v1);
	new.x = v1.x / length;
	new.y = v1.y / length;
	new.z = v1.z / length;
	return (new);
}

float			length_vector3d(t_vector3d v1)
{
	return (sqrtf(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z));
}
