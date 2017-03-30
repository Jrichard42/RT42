/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramide_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 19:41:19 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/30 19:41:20 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pyramide.h"
#define PYRA ((t_pyra *)obj->data)
#define FLOAT_ZERO 0.0001f

float		inter_pyra(t_obj *obj, t_ray *ray)
{
	float	inter;
	float	tmp;
	int		i;

	inter = NAN;
	i = 0;
	while (i < 6)
	{
		tmp = inter_triangles(&PYRA->face[i], ray);
		if (((!isnan(tmp) && tmp < inter) || (!isnan(tmp) &&
						isnan(inter))))
			inter = tmp;
		i++;
	}
	if (inter < 0)
		inter = NAN;
	return (inter);
}

int			create_pyra3(t_kvlexer *token, t_rt *rt, t_obj *obj)
{
	if (!get_material(token, rt, &(obj->mat)))
		return (0);
	if (!get_texture(token, rt, &(obj->tex)))
		obj->texture = NULL;
	if (!get_as_vector3f(token, "POS", &(obj->pos)))
		return ((int)ft_error("The PYRAMIDE should contain a field POS"));
	if (!get_as_int(token, "ID", &(obj->id)))
		return ((int)ft_error("The PYRAMIDE should contain a field ID"));
	if (!get_as_int(token, "IS_SRC", &(obj->is_src)))
		return ((int)ft_error("The PYRAMIDE should contain a field IS_SRC"));
	if (obj->is_src)
		obj->light = get_light(token);
	return (1);
}
