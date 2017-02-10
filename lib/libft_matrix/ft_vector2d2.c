/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2d2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 19:05:23 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/10 19:05:55 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_vector2d.h"

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
