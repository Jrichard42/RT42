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

static t_res	fin(float u, float aa, float bb, float bs)
{
	float	uma;
	float	d;
	t_res	res;

	res.x1 = NAN;
	res.x2 = NAN;
	res.x3 = NAN;
	res.x4 = NAN;
	res.nb = 0;
	uma = u - aa;
	d = uma - 4 * (bb / 2 / uma * sqrtf(uma) + u / 2);
	if (d >= 0)
	{
		res.nb += 2;
		res.x1 = (sqrtf(uma) + sqrtf(d)) / 2 - bs;
		res.x2 = (sqrtf(uma) - sqrtf(d)) / 2 - bs;
	}
	d = uma - 4 * (-bb / 2 / uma * sqrtf(uma) + u / 2);
	if (d >= 0)
	{
		res.nb += 2;
		res.x3 = (-sqrtf(uma) + sqrtf(d)) / 2 - bs;
		res.x4 = (-sqrtf(uma) - sqrtf(d)) / 2 - bs;
	}
	return (res);
}

static t_res	delta_negative(t_equ var, t_res res)
{
	if (var.p != 0)
	{
		var.kos = -var.q / 2 / sqrtf(-var.p * var.p * var.p / 27);
		var.r = sqrtf(-var.p / 3);
	}
	if (absf(var.kos) - 1 < exp(-14))
		var.alpha = -M_PI * (var.kos - 1) / 2;
	else
		var.alpha = acos(var.kos);
	res.x1 = 2 * var.r * cos((var.alpha) / 3) + var.vt;
	res.x2 = 2 * var.r * cos((var.alpha + 2 * 1 * M_PI) / 3) + var.vt;
	res.x3 = 2 * var.r * cos((var.alpha + 2 * 2 * M_PI) / 3) + var.vt;
	if (var.r == 0)
		return (fin(res.x1, var.aa, var.bb, var.bs));
	else if (res.x1 > var.aa)
		return (fin(res.x1, var.aa, var.bb, var.bs));
	var.u = res.x2;
	if (res.x3 > var.aa)
		var.u = res.x3;
	return (fin(var.u, var.aa, var.bb, var.bs));
}

static void		var_init(t_equ *var, t_res *res, float *val)
{
	res->x1 = NAN;
	res->x2 = NAN;
	res->x3 = NAN;
	res->x4 = NAN;
	res->nb = 0;
	var->bs = val[1] / 4 / val[0];
	var->aa = -3 * val[1] * val[1] / 8 / val[0] / val[0] + val[2] / val[0];
	var->ma = -var->aa;
	var->bb = val[1] * val[1] * val[1] / 8 / val[0] / val[0] / val[0] - val[1]
	* val[2] / 2 / val[0] / val[0] + val[3] / val[0];
	var->cc = -3 * val[1] * val[1] * val[1] * val[1] / 256 / val[0] / val[0]
	/ val[0] / val[0] + val[2] * val[1] * val[1] / 16 / val[0] / val[0]
	/ val[0] - val[1] * val[3] / 4 / val[0] / val[0] + val[4] / val[0];
	var->mc = -4 * var->cc;
	var->k = 4 * var->aa * var->cc - var->bb * var->bb;
	var->kos = 0;
	var->r = 0;
}

static void		var_calcul(t_equ *var, float *val)
{
	var->bs = val[1] / 4 / val[0];
	val[0] = 1;
	val[1] = -var->aa;
	val[2] = var->mc;
	val[3] = var->k;
	var->vt = -val[1] / 3 / val[0];
	var->p = val[2] / val[0] - val[1] * val[1] / 3 / val[0] / val[0];
	var->q = val[1] * val[1] * val[1] / val[0] / val[0] / val[0] / 13.5
	+ val[3] / val[0] - val[1] * val[2] / 3 / val[0] / val[0];
	if (absf(var->p) < exp(-14))
		var->p = 0;
	if (absf(var->q) < exp(-14))
		var->q = 0;
	var->del = var->q * var->q / 4 + var->p * var->p * var->p / 27;
	if (absf(var->del) < exp(-14))
		var->del = 0;
}

t_res			equationpoly4(float *val)
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
