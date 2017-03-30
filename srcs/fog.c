/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 15:05:29 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/30 15:20:53 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fog.h"

int					create_fog(t_kvlexer *token, t_rt *rt)
{
	if (!(rt->fog = (t_fog*)malloc(sizeof(t_fog))))
		return (0);
	if (!get_as_vector3f(token, "COLOR", &rt->fog->color))
		return ((int)ft_error("The FOG should contain a field COLOR"));
	if (!get_as_float(token, "DISTANCE", &rt->fog->distance))
		return ((int)ft_error("The FOG should contain a field DISTANCE"));
	if (!get_as_float(token, "TYPE", &rt->fog->type))
		return ((int)ft_error("The FOG should contain a field TYPE"));
	if (rt->fog->type > 2.f || rt->fog->type < 1.f)
		return ((int)ft_error("The FOG TYPE should be one or two"));
	return (1);
}

static t_vector3f	fog_exp_squared(t_rt *rt, t_inter *inter, t_vector3f color)
{
	color = add_vector3f(mult_vector3f(rt->fog->color, 1 -
			exp(-(inter->distance / rt->fog->distance) *
			(inter->distance / rt->fog->distance))),
			mult_vector3f(color, exp(-(inter->distance / rt->fog->distance)
			* (inter->distance / rt->fog->distance))));
	return (color);
}

static t_vector3f	fog_exp(t_rt *rt, t_inter *inter, t_vector3f color)
{
	color = add_vector3f(mult_vector3f(rt->fog->color, 1 -
			exp(-(inter->distance / rt->fog->distance))),
			mult_vector3f(color, exp(-(inter->distance / rt->fog->distance))));
	return (color);
}

t_vector3f			fog(t_rt *rt, t_inter *inter, t_vector3f color)
{
	if (!rt->fog)
		return (color);
	if (rt->fog->type == 1.f)
	{
		if (inter->distance > rt->fog->distance * 4 || isnan(inter->distance))
			return (rt->fog->color);
		else
			return (fog_exp_squared(rt, inter, color));
	}
	else if (rt->fog->type == 2.f)
	{
		if (inter->distance > rt->fog->distance * 5 || isnan(inter->distance))
			return (rt->fog->color);
		else
			return (fog_exp(rt, inter, color));
	}
	return (color);
}
