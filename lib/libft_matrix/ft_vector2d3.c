/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2d3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 13:04:52 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/25 13:12:26 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_vector2d.h"

float			squared_length_vector2d(t_vector2d v1)
{
	return (v1.x * v1.x + v1.y * v1.y);
}

t_vector2d		clamp_vector2d(t_vector2d v1, double min, double max)
{
	t_vector2d	new;

	new = v1;
	if (new.x < min)
		new.x = min;
	else if (new.x > max)
		new.x = max;
	if (new.y < min)
		new.y = min;
	else if (new.y > max)
		new.y = max;
	return (new);
}
