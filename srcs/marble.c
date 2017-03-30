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

static	void		check_error_marble_annex(t_vector2f *size_tmp)
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

static	void		check_error_marble(t_vector2f *size_tmp, t_marble *marble)
{
	if (marble->turb.x < 1 || marble->turb.x > 1000)
		marble->turb.x = 10;
	if (marble->turb.y < 1 || marble->turb.y > 1000)
		marble->turb.y = 64;
	if (marble->period.x < 1 || marble->period.x > 1000)
		marble->period.x = 5;
	if (marble->period.y < 1 || marble->period.y > 1000)
		marble->period.y = 10;
	check_error_marble_annex(size_tmp);
}

unsigned int		marble2(t_vector2f pixel,
							double ***noise,
							t_marble marble,
							t_vector2f size)
{
	double			xyvalue;
	double			sinevalue;

	if (pixel.y <= size.y && pixel.y <= size.x)
	{
		xyvalue = (pixel.x * marble.period.x / size.x + pixel.y *
			marble.period.y / size.y + marble.turb.x *
			turbulence(pixel, marble.turb.y, *noise, size)) / 256;
		sinevalue = 256 * fabs(sin(xyvalue * M_PI));
		return ((unsigned int)sinevalue);
	}
	return (0);
}

static	int			marble_tableau(t_vector2f size,
									t_vector3f ***texture,
									t_marble marble,
									double **noise)
{
	t_vector2f		point;
	t_vector3f		color;

	point.y = -1;
	while (++point.y < size.y)
	{
		point.x = -1;
		while (++point.x < size.x)
		{
			color.x = 30 + marble2(point, &noise, marble, size);
			color.y = 10 + marble2(point, &noise, marble, size);
			color.z = marble2(point, &noise, marble, size);
			(*texture)[(int)point.y][(int)point.x] = color;
		}
	}
	return (1);
}

int					marble_tex(t_kvlexer *token, t_texture *tex)
{
	double			**noise;
	t_vector2f		size;
	t_marble		marble;

	if (!get_as_vector2f(token, "TURB", &(marble.turb)))
		return ((int)ft_error("The TURB should contain a field 2 floats"));
	if (!get_as_vector2f(token, "PERIOD", &(marble.period)))
		return ((int)ft_error("The period should contain a field 2 floats"));
	if (!get_as_vector2f(token, "SIZE", &(size)))
		return ((int)ft_error("The SIZE should contain 2 floats"));
	check_error_marble(&size, &marble);
	tex->height = size.y;
	tex->width = size.x;
	if (!malloc_tex(tex))
		return (0);
	if (!bruit_perlin(size, &noise))
		return (0);
	if (!marble_tableau(size, &tex->data, marble, noise))
		return (0);
	free_tab(noise, size);
	return (1);
}
