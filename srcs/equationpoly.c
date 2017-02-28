/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equationpoly.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:01:59 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/02/21 13:02:02 by jqueyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "equation.h"

t_res	equationpoly(float *val, int lenght)
{
	t_res res;

	res.x1 = NAN;
	res.x2 = NAN;
	res.x3 = NAN;
	res.x4 = NAN;
	if (lenght == 5)
		return (equationpoly4(val));
	if (lenght == 4)
		return (equationpoly3(val[0], val[1], val[2], val[3]));
	if (lenght == 3)
		return (equationpoly2(val[0], val[1], val[2]));
	if (lenght == 2)
		return (equationpoly1(val[0], val[1]));
	return (res);
}
