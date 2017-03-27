/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wood.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:54:10 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/13 15:54:12 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "rt.h"
#include "light.h"
#include "bruit_perlin.h"

void		remplissage_tableau(t_vector2f size, double ***texture, t_vector3d modif_wood)
{
	t_vector2f	point;
	t_vector3f	color;

	point.y = -1;
	while (++point.y < size.y)
	if (!(texture = (t_vector3f **)malloc(sizeof(t_vector3f *) * size.y)))
		return (NULL);
	{
		point.x = -1;
		if (!(texture[(int)point.y] = (t_vector3f *)malloc(sizeof(t_vector3f) * size.x)))
			return (NULL);
		while (++point.x < size.x)
		{
			color.x = 130 + wood(point, &texture, modif_wood, t_vector2f size);
			color.y = 60 + wood(point, &texture, modif_wood, t_vector2f size);
			color.z = 19;
			texture[(int)point.y][(int)point.x] = color;
		}
	}
}

unsigned int	wood(t_vector2f pixel, double ***texture, t_vector3d modif_wood, t_vector2f size)
{
	t_vector2f	value;
	t_vector2f	dist_and_sine_value;

	// modif_wood.x = periode
	// modif_wood.y = turbulence power
	// modif_wood.z = trubulence size
	if (pixel.y <= size.y && pixel.y <= size.x)
	{
		value.x = (pixel.x - size.x / 2) / (double)size.x;
		value.y = (pixel.y - size.y / 2) / (double)size.y;
		dist_and_sine_value.x = sqrt(value.x * value.x + value.y * value.y)
		+ modif_wood.y * turbulence(pixel.x, pixel.y, modif_wood.z, noise) / 256.0;
		dist_and_sine_value.y = 128.0 *
		fabs(sin(2 * modif_wood.x * dist_and_sine_value.x * M_PI));
		return ((unsigned int)dist_and_sine_value.y);
	}
	return (0);
}

t_vector3f		**wood_text(t_kvlexer *token, t_rt, *rt, t_texture *tex)
{
	static	double	**noise;
	static	int 	marque;
	char			*type;
	t_vector2f		size;
	t_vector3d		modif_wood;

	if (!get_as_vector3d(token, "MODIF_WOOD", &(modif_wood)))
		return ((int)ft_error("The MODIF_WOOD should contain a field 3 double"));
	if (!get_as_string(token, "TYPE", &(type)))
		return ((int)ft_error("The TYPE should contain texture name"));
	if (!get_as_string(token, "SIZE", &(size)))
		return ((int)ft_error("The SIZE should contain 2 floats"));
	bruit_perlin(size, type, noise);
	if (ft_strcmp("WOOD", type) == 0)
		remplissage_tableau(size, &text->data, modif_wood);
}
