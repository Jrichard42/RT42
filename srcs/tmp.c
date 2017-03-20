/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 17:00:11 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/16 17:00:12 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "camera.h"
#include "light.h"
#include "bruit_perlin.h"

t_vector3f			**create_texture_tab(char *type)
{
	t_vector3f	**texture;
	t_vector2f	point;

	point.y = -1;
	if (!(texture = (t_vector3f **)malloc(sizeof(t_vector3f *) * 1080)))
		return (NULL);
	while (++point.y < 1080)
	{
		point.x = -1;
		if (!(texture[(int)point.y] = (t_vector3f *)malloc(sizeof(t_vector3f) * 1920)))
			return (NULL);
		while (++point.x < 1920)
			texture[(int)point.y][(int)point.x] = bruit_perlin(point, type);
	}
	return (texture);
}
