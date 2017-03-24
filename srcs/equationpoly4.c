/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equationpoly4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:46:51 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/02/21 13:46:53 by jqueyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "equation.h"

static t_res	fin(double u, double aa, double bb, double bs)
{
	double	uma;
	double	d;
	t_res	res;

	res.x1 = NAN;
	res.x2 = NAN;
	res.x3 = NAN;
	res.x4 = NAN;
	res.nb = 0;
	uma = u - aa;
	d = uma - (double)4.0 * (bb / (double)2 / uma * sqrt(uma) + u / (double)2);
	if (d >= 0)
	{
		res.nb += 2;
		res.x1 = (double)(sqrt(uma) + sqrt(d)) / (double)2 - bs;
		res.x2 = (double)(sqrt(uma) - sqrt(d)) / (double)2 - bs;
	}
	d = uma - (double)4.0 * (-bb / 2.0f / uma * sqrt(uma) + u / (double)2);
	if (d >= 0)
	{
		res.nb += 2;
		res.x3 = (double)(-sqrt(uma) + sqrt(d)) / (double)2 - bs;
		res.x4 = (double)(-sqrt(uma) - sqrt(d)) / (double)2 - bs;
	}
	return (res);
}

static t_res	delta_negative(t_equ var, t_res res)
{
	if (var.p != 0)
	{
		var.kos = -var.q / (double)2 /
		sqrt(-var.p * var.p * var.p / (double)27);
		var.r = sqrt(-var.p / (double)3);
	}
	var.alpha = acos(var.kos);
	res.x1 = (double)2 * var.r * cos((var.alpha) / (double)3) + var.vt;
	res.x2 = (double)2 * var.r * cos((var.alpha + (double)2 *
		M_PI) / (double)3) + var.vt;
	res.x3 = (double)2 * var.r * cos((var.alpha + (double)2 *
		(double)2 * M_PI) / (double)3) + var.vt;
	if (var.r == 0)
		return (fin(res.x1, var.aa, var.bb, var.bs));
	else if (res.x1 > var.aa)
		return (fin(res.x1, var.aa, var.bb, var.bs));
	var.u = res.x2;
	if (res.x3 > var.aa)
		var.u = res.x3;
	return (fin(var.u, var.aa, var.bb, var.bs));
}

static void		var_init(t_equ *var, t_res *res, double *val)
{
	res->x1 = NAN;
	res->x2 = NAN;
	res->x3 = NAN;
	res->x4 = NAN;
	res->nb = 0;
	var->bs = val[1] / (double)4 / val[0];
	var->aa = -(double)3 * val[1] * val[1] / 8 /
	val[0] / val[0] + val[2] / val[0];
	var->ma = -var->aa;
	var->bb = val[1] * val[1] * val[1] / 8 / val[0] / val[0] / val[0] - val[1]
	* val[2] / 2 / val[0] / val[0] + val[3] / val[0];
	var->cc = -(double)3 * val[1] * val[1] * val[1] * val[1]
	/ (double)256 / val[0] / val[0]
	/ val[0] / val[0] + val[2] * val[1] * val[1] / (double)16 / val[0] / val[0]
	/ val[0] - val[1] * val[3] / (double)4 / val[0] / val[0] + val[4] / val[0];
	var->mc = -(double)4 * var->cc;
	var->k = (double)4 * var->aa * var->cc - var->bb * var->bb;
	var->kos = (double)0;
	var->r = (double)0;
}

static void		var_calcul(t_equ *var, double *val)
{
	var->bs = val[1] / (double)4 / val[0];
	val[0] = (double)1;
	val[1] = -var->aa;
	val[2] = var->mc;
	val[3] = var->k;
	var->vt = -val[1] / 3 / val[0];
	var->p = val[2] / val[0] - val[1] * val[1] / (double)3 / val[0] / val[0];
	var->q = val[1] * val[1] * val[1] / val[0] / val[0] / val[0] / (double)13.5
	+ val[3] / val[0] - val[1] * val[2] / (double)3 / val[0] / val[0];
	var->del = var->q * var->q / (double)4 +
	var->p * var->p * var->p / (double)27;
}

t_res			equationpoly4(double *val)
{
	t_res	res;
	t_equ	var;

	var_init(&var, &res, val);
	if (absf(var.bb) < exp(-12))
		return (equationpoly2(1, var.aa, var.cc));
	var_calcul(&var, val);
	if (var.del <= 0)
		return (delta_negative(var, res));
	else
	{
		var.u = uv(var.del, var.q, 1) + uv(var.del, var.q, -1)
		+ var.vt;
	}
	return (fin(var.u, var.aa, var.bb, var.bs));
}
