/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:10:05 by dbreton           #+#    #+#             */
/*   Updated: 2017/02/18 18:18:11 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "utils.h"

char			almost_equal_relative(float a, float b)
{
	double		diff;
	double		largest;

	diff = fabs(a - b);
	a = fabs(a);
	b = fabs(b);
	largest = (b > a) ? b : a;
	return (diff <= largest * FLT_EPSILON);
}
