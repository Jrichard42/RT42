/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equationpoly3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 12:53:01 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/02/21 12:53:06 by jqueyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "equation.h"

int				sgn(double x)
{
	return ((x > 0) - (x < 0));
}

double			absf(double x)
{
	return (x * sgn(x));
}

double			uv(double delta, double q, double sg)
{
	double r;
	double z;

	r = sqrt(delta) * sg;
	z = (-q / 2) + r;
	return (sgn(z) * cbrt(absf(z)));
}

static	t_res	delta_negative(t_equ var, t_res res)
{
	if (var.p != 0)
	{
		var.kos = -var.q / 2 / sqrt(-var.p * var.p * var.p / 27);
		var.r = sqrt(-var.p / 3);
	}
	else
	{
		var.kos = 0;
		var.r = 0;
	}
	if (absf(var.kos == 1))
		var.alpha = -M_PI * (var.kos - 1) / 2;
	else
		var.alpha = acos(var.kos);
	res.x1 = 2 * var.r * cos((var.alpha) / 3) + var.vt;
	res.x2 = 2 * var.r * cos((var.alpha + 2 * 1 * M_PI) / 3) + var.vt;
	res.x3 = 2 * var.r * cos((var.alpha + 2 * 2 * M_PI) / 3) + var.vt;
	res.nb = 3;
	return (res);
}

t_res			equationpoly3(double a, double b, double c, double d)
{
	t_equ var;
	t_res res;

	var.vt = -b / 3 / a;
	var.p = c / a - b * b / 3 / a / a;
	var.q = b * b * b / a / a / a / 13.5 + d / a - b * c / 3 / a / a;
	res.x1 = NAN;
	res.x2 = NAN;
	res.x3 = NAN;
	res.x4 = NAN;
	res.nb = 0;
	var.del = ((var.q * var.q) / 4) + ((var.p * var.p * var.p) / 27);
	if (absf(var.p) < exp(-14))
		var.p = 0;
	if (absf(var.q) < exp(-14))
		var.q = 0;
	if (var.del <= 0)
		return (delta_negative(var, res));
	else
	{
		res.x1 = uv(var.del, var.q, 1) + uv(var.del, var.q, -1) + var.vt;
		res.nb = 1;
	}
	return (res);
}
