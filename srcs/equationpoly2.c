/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equationpoly2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:00:45 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/02/21 13:00:50 by jqueyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "equation.h"

t_res	equationpoly2(float a, float b, float c)
{
	t_res res;
	float delta;

	res.x1 = NAN;
	res.x2 = NAN;
	res.x3 = NAN;
	res.x4 = NAN;
	res.nb = 0;
	delta = b * b - (4 * a * c);
	if (delta > 0)
	{
		delta = sqrt(delta);
		res.nb = 2;
		res.x1 = (-b - delta) / (2 * a);
		res.x2 = (-b + delta) / (2 * a);
	}
	else if (delta == 0)
	{
		res.x1 = -b / (2 * a);
		res.nb = 1;
	}
	return (res);
}
