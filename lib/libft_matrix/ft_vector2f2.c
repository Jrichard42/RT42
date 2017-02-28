/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2f2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 19:07:10 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/25 12:56:43 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_vector2f.h"

float			dot_vector2f(t_vector2f v1, t_vector2f v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

t_vector2f		normalize_vector2f(t_vector2f v1)
{
	t_vector2f	new;
	float		inv_length;

	inv_length = length_vector2f(v1);
	new.x = v1.x * inv_length;
	new.y = v1.y * inv_length;
	return (new);
}

float			length_vector2f(t_vector2f v1)
{
	return (sqrtf(v1.x * v1.x + v1.y * v1.y));
}
