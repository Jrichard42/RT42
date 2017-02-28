/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3d3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 13:04:52 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/25 13:12:38 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_vector3d.h"

float			squared_length_vector3d(t_vector3d v1)
{
	return (v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
}

t_vector3d		clamp_vector3d(t_vector3d v1, double min, double max)
{
	t_vector3d	new;

	new = v1;
	if (new.x < min)
		new.x = min;
	else if (new.x > max)
		new.x = max;
	if (new.y < min)
		new.y = min;
	else if (new.y > max)
		new.y = max;
	if (new.z < min)
		new.z = min;
	else if (new.z > max)
		new.z = max;
	return (new);
}
