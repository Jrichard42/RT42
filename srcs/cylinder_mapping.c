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

t_vector3f			cylinder_mapping(t_vector3f inter_obj, t_vector3f **texture)
{
	t_vector3f		color;
	static	int		tmp;

	color = create_vector3f(0, 0, 0);
	if (inter_obj.x < 0)
		inter_obj.x = -inter_obj.x;
	if (inter_obj.y < 0)
		inter_obj.y = -inter_obj.y;
	if (inter_obj.x < 1)
		inter_obj.x = 1;
	if (inter_obj.y < 1)
		inter_obj.y = 1;
	if (tmp < 100)
	{
		tmp++;
		color.x = 255;
		color.y = color.z = 0;
		return (color);
	}
	printf("%f|%f\n", inter_obj.x, inter_obj.y);
	color = texture[(int)(inter_obj.y)][(int)(inter_obj.x)];
	// printf("color %f|%f|%f\n", color.x, color.y, color.z);
	return (color);
}
