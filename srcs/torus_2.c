/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 20:01:19 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/30 20:01:20 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "torus.h"

float			resolution(double *eq)
{
	double	inter;
	t_res	res;

	res = equationpoly4(eq);
	inter = NAN;
	if (!isnan(res.x1))
		inter = res.x1;
	if (((!isnan(res.x2) && res.x2 < inter) || (!isnan(res.x2) &&
					isnan(inter))))
		inter = res.x2;
	if (((!isnan(res.x3) && res.x3 < inter) || (!isnan(res.x3) &&
					isnan(inter))))
		inter = res.x3;
	if (((!isnan(res.x4) && res.x4 < inter) || (!isnan(res.x4) &&
					isnan(inter))))
		inter = res.x4;
	if (inter < 0)
		inter = NAN;
	free(eq);
	return (inter);
}
