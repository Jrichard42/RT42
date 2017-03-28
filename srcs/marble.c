/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marble.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:54:10 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/13 15:54:12 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bruit_perlin.h"

unsigned int	marble2(t_vector2f pixel, double ***texture, t_marble marble, t_vector2f size)
{
	double		xyvalue;
	double		sinevalue;

	// marble.period = periode (x et y)
	// marble.turb.x = turbpower
	// marble.turb.y = turbsize 
	if (pixel.y <= size.y && pixel.y <= size.x)
	{
		xyvalue = (pixel.x * marble.period.x / size.x + marble.pixel.y *
			period.y / size.y + marble.turb.x *
			turbulence(pixel.x, pixel.y, marble.turb.y, noise)) / 256;
		sinevalue = 256 * fabs(sin(xyvalue * M_PI));
		return ((unsigned int)sinevalue);
	}
	return (0);
}

int			remplissage_tableau(t_vector2f size, t_vector3f ***texture, t_marble marble, double **noise)
{
	t_vector2f	point;
	t_vector3f	color;

	point.y = -1;
	while (++point.y < size.y)
	{
		point.x = -1;
		while (++point.x < size.x)
		{
			color.x = 30 + marble(pixel, noise);
			color.y = 10 + marble(pixel, noise);
			color.z = marble(pixel, noise);
			*texture[(int)point.y][(int)point.x] = color;
		}
	}
	return (1);
}

int			marble_text(t_kvlexer *token, t_texture *tex)
{
	double			**noise;
	char			type;
	t_vector2f		size;
	t_marble		marble;

	if (!get_as_vector3f(token, "TURB", &(marble.turb)))
		return ((int)ft_error("The TURB should contain a field 2 floats"));
	if (!get_as_vector3f(token, "PERIOD", &(marble.period)))
		return ((int)ft_error("The period should contain a field 2 floats"));
	if (!get_as_vector2f(token, "SIZE", &(size)))
		return ((int)ft_error("The SIZE should contain 2 floats"));
	tex->height = size.y;
	tex->width = size.x;
	if (!malloc_tex(tex))
		return (0);
	if (!bruit_perlin(size, &noise))
		return (0);
	if (!remplissage_tableau(size, &tex->data, modif_wood, noise))
		return (0);
	return (1);
}
