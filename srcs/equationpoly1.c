/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equationpoly1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:01:34 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/02/21 13:01:37 by jqueyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "equation.h"

t_res	equationpoly1(float a, float b)
{
	t_res res;

	res.x1 = NAN;
	res.x2 = NAN;
	res.x3 = NAN;
	res.x4 = NAN;
	res.nb = 1;
	res.x1 = -b / a;
	return (res);
}
