/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <jrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 14:31:42 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/25 12:53:51 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_vector3f.h"

t_vector3f		create_vector3f(float x, float y, float z)
{
	t_vector3f	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_vector3f		add_vector3f(t_vector3f v1, t_vector3f v2)
{
	t_vector3f	new;

	new.x = v1.x + v2.x;
	new.y = v1.y + v2.y;
	new.z = v1.z + v2.z;
	return (new);
}

t_vector3f		sub_vector3f(t_vector3f v1, t_vector3f v2)
{
	t_vector3f	new;

	new.x = v1.x - v2.x;
	new.y = v1.y - v2.y;
	new.z = v1.z - v2.z;
	return (new);
}

t_vector3f		mult_vector3f(t_vector3f v1, float nb)
{
	t_vector3f	new;

	new.x = v1.x * nb;
	new.y = v1.y * nb;
	new.z = v1.z * nb;
	return (new);
}

t_vector3f		div_vector3f(t_vector3f v1, float nb)
{
	t_vector3f	new;

	nb = 1.0f / nb;
	new.x = v1.x * nb;
	new.y = v1.y * nb;
	new.z = v1.z * nb;
	return (new);
}
