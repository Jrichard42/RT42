/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_mapping.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 16:36:29 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/16 16:36:30 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "rt.h"
#include "light.h"
#include "obj.h"
#include "inter.h"

//t_vector3f			cylinder_mapping(t_inter inter_obj, t_vector3f **texture)
//{
	// t_vector3f		color; ici
	// t_vector3f		pos; ici
	// t_vector3f		uv; ici

	//pos = sub_vector3f(inter_obj.obj->pos, inter_obj.impact);ici
/*	if (pos.z != 0.0f)
	{
		uv.x = pos.x / pos.z;
		uv.y = pos.y / pos.z;
	}
	else
	{*/
		//uv.x = pos.x; ici
		//uv.y = pos.y; ici
	//}
	//uv.x = fabsf(uv.x); ici
	//uv.y = fabsf(uv.y); ici
	//printf("%f|%f\n", inter_obj.impact.x, inter_obj.impact.y);
	//color = texture[(int)(abs(inter_obj.impact.y - inter_obj.obj->pos.y))][(int)abs((inter_obj.impact.x - inter_obj.obj->pos.x))];
	//color = texture[(int)uv.y % 1079][(int)uv.x % 1919]; ici
	// printf("color %f|%f|%f\n", color.x, color.y, color.z);
	//return (color); ici
//}
