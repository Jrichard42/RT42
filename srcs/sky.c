/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:54:10 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/13 15:54:12 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bruit_perlin.h"
#include "texture.h"

static	void		check_error_sky(t_vector2f *size_tmp, float *sky)
{
	if (size_tmp->x < 10)
	{
		size_tmp->x = 10;
		ft_putstr("The X_SIZE are inferior to 10\n");
	}
	if (size_tmp->x > 2000)
	{
		size_tmp->x = 2000;
		ft_putstr("The X_SIZE are superior to 2000\n");
	}
	if (size_tmp->y < 10)
	{
		size_tmp->y = 100;
		ft_putstr("The Y_SIZE are inferior to 10\n");
	}
	if (size_tmp->y > 2000)
	{
		size_tmp->y = 2000;
		ft_putstr("The Y_SIZE are superior to 2000\n");
	}
	if (*sky < 8 || *sky > 128)
		*sky = 64;
}

static	int			sky_tableau(t_vector2f size,
								t_vector3f ***texture,
								float modif_sky,
								double **noise)
{
	t_vector2f	point;
	t_vector3f	color;
	float		l;

	l = 0;
	point.y = -1;
	while (++point.y < size.y)
	{
		point.x = -1;
		while (++point.x < size.x)
		{
			l = (192 + (unsigned int)(
				turbulence(point, modif_sky, noise, size))) / 4;
			color = hsl_to_rgb(240, 100, l);
			(*texture)[(int)point.y][(int)point.x] = color;
		}
	}
	return (1);
}

int					sky_tex(t_kvlexer *token, t_texture *tex)
{
	double			**noise;
	t_vector2f		size;
	float			modif_sky;

	if (!get_as_float(token, "MODIF_SKY", &modif_sky))
		return ((int)ft_error("The POINT should contain a value"));
	if (!get_as_vector2f(token, "SIZE", &size))
		return ((int)ft_error("The SIZE should contain 2 floats"));
	check_error_sky(&size, &modif_sky);
	tex->height = size.y;
	tex->width = size.x;
	if (!malloc_tex(tex))
		return (0);
	if (bruit_perlin(size, &noise) == 0)
		return (0);
	if (!sky_tableau(size, &tex->data, modif_sky, noise))
		return (0);
	return (1);
}
