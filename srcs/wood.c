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

#include "bruit_perlin.h"
#include "texture.h"

static	void	check_error_wood_annex(t_vector2f *size_tmp)
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
}

static	void	check_error_wood(t_vector2f *size_tmp, t_vector3f *modif_wood)
{
	check_error_wood_annex(size_tmp);
	if (modif_wood->x < 1 || modif_wood->x > 100)
		modif_wood->x = 12;
	if (modif_wood->y < 1 || modif_wood->y > 100)
		modif_wood->y = 0.05;
	if (modif_wood->z < 1 || modif_wood->z > 100)
		modif_wood->z = 24;
}

unsigned int	wood2(t_vector2f pixel, double ***texture, t_vector3f modif_wood, t_vector2f size)
{
	t_vector2f	value;
	t_vector2f	dist_and_sine_value;

	if (pixel.y <= size.y && pixel.y <= size.x)
	{
		value.x = (pixel.x - size.x / 2) / (double)size.x;
		value.y = (pixel.y - size.y / 2) / (double)size.y;
		dist_and_sine_value.x = sqrt(value.x * value.x + value.y * value.y)
		+ modif_wood.y * turbulence(pixel, modif_wood.z, *texture, size) / 256.0;
		dist_and_sine_value.y = 128.0 *
		fabs(sin(2 * modif_wood.x * dist_and_sine_value.x * M_PI));
		return ((unsigned int)dist_and_sine_value.y);
	}
	return (0);
}

static	int		wood_tableau(t_vector2f size, t_vector3f ***texture, t_vector3f modif_wood, double **noise)
{
	t_vector2f	point;
	t_vector3f	color;

	point.y = -1;
	while (++point.y < size.y)
	{
		point.x = -1;
		while (++point.x < size.x)
		{
			color.x = 130 + wood2(point, &noise, modif_wood, size);
			color.y = 60 + wood2(point, &noise, modif_wood, size);
			color.z = 19;
			(*texture)[(int)point.y][(int)point.x] = color;
		}
	}
	return (1);
}

int			wood_tex(t_kvlexer *token, t_texture *tex)
{
	double			**noise;
	t_vector2f		size;
	t_vector3f		modif_wood;

	if (!get_as_vector3f(token, "MODIF_WOOD", &(modif_wood)))
		return ((int)ft_error("The MODIF_WOOD should contain a field 3 double"));
	if (!get_as_vector2f(token, "SIZE", &(size)))
		return ((int)ft_error("The SIZE should contain 2 floats"));
	check_error_wood(&size, &modif_wood);
	tex->height = size.y;
	tex->width = size.x;
	if (!malloc_tex(tex))
		return (0);
	if (bruit_perlin(size, &noise) == 0)
		return (0);
	if (!wood_tableau(size, &tex->data, modif_wood, noise))
		return (0);
	return (1);
}
