/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <jrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 14:31:42 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/12 19:27:12 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_vector2d.h"

t_vector2d		create_vector2d(double x, double y)
{
	t_vector2d	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

t_vector2d		add_vector2d(t_vector2d v1, t_vector2d v2)
{
	t_vector2d	new;

	new.x = v1.x + v2.x;
	new.y = v1.y + v2.y;
	return (new);
}

t_vector2d		sub_vector2d(t_vector2d v1, t_vector2d v2)
{
	t_vector2d	new;

	new.x = v1.x - v2.x;
	new.y = v1.y - v2.y;
	return (new);
}

t_vector2d		mult_vector2d(t_vector2d v1, float nb)
{
	t_vector2d  new;

	new.x = v1.x * nb;
	new.y = v1.y * nb;
	return (new);
}

t_vector2d		div_vector2d(t_vector2d v1, float nb)
{
	t_vector2d  new;

	new.x = v1.x * nb;
	new.y = v1.y * nb;
	return (new);
}

double			dot_vector2d(t_vector2d v1, t_vector2d v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

t_vector2d		normalize_vector2d(t_vector2d v1)
{
	t_vector2d	new;
	float		length;

	length = length_vector2d(v1);
	new.x = v1.x / length;
	new.y = v1.y / length;
	return (new);
}

float			length_vector2d(t_vector2d v1)
{
	return (sqrtf(v1.x * v1.x + v1.y * v1.y));
}
