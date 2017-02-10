/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <jrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 14:31:42 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/06 11:30:24 by jrichard         ###   ########.fr       */
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
	t_vector3f  new;

	new.x = v1.x * nb;
	new.y = v1.y * nb;
	new.z = v1.z * nb;
	return (new);
}

t_vector3f		div_vector3f(t_vector3f v1, float nb)
{
	t_vector3f  new;

	new.x = v1.x / nb;
	new.y = v1.y / nb;
	new.z = v1.z / nb;
	return (new);
}

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
	float		length;

	length = length_vector3f(v1);
	new.x = v1.x / length;
	new.y = v1.y / length;
	new.z = v1.z / length;
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
	new.x = transf->tab[0][0] * v1.x + transf->tab[0][1] * v1.y + transf->tab[0][2] * v1.z + transf->tab[0][3];
	new.y = transf->tab[1][0] * v1.x + transf->tab[1][1] * v1.y + transf->tab[1][2] * v1.z + transf->tab[1][3];
	new.z = transf->tab[2][0] * v1.x + transf->tab[2][1] * v1.y + transf->tab[2][2] * v1.z + transf->tab[2][3];
	return (new);
}
