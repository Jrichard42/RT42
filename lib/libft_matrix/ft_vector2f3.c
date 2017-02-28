/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2f3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 13:06:32 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/25 13:08:23 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_vector2f.h"

float			squared_length_vector2f(t_vector2f v1)
{
	return (v1.x * v1.x + v1.y * v1.y);
}

t_vector2f		clamp_vector2f(t_vector2f v1, float min, float max)
{
	t_vector2f	new;

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
