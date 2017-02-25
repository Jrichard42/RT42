/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <jrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 14:31:42 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/25 12:53:54 by jrichard         ###   ########.fr       */
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
	t_vector3d	new;

	new.x = v1.x * nb;
	new.y = v1.y * nb;
	new.z = v1.z * nb;
	return (new);
}

t_vector3d		div_vector3d(t_vector3d v1, float nb)
{
	t_vector3d	new;

	nb = 1.0f / nb;
	new.x = v1.x * nb;
	new.y = v1.y * nb;
	new.z = v1.z * nb;
	return (new);
}
