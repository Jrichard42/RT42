/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toto.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 17:39:59 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/15 19:34:13 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void                put_in_image(t_mlx *s, int x, int y, t_color color)
{
	unsigned int    pixel_position;

	if ((x < s->wh[0]) && y < (s->wh[1]))
	{
		pixel_position = y * (s->pitch / sizeof(unsigned int)) + x;
		s->pixels[pixel_position] = get_color_value(color);
	}
}

static int            is_closest(double *d, double *res)
{
	int                i;
	double            d_init;

	i = 1;
	d_init = *d;
	while (i <= (int)res[0])
	{
		*d = (res[i] > 0 && *d > res[i]) ? res[i] : *d;
		++i;
	}
	return (d_init != *d);
}

static t_vector        create_vector(t_mlx *s, int i, int j)
{
	t_vector        v;
	t_vector        vpp;

	vpp = add_vector(s->cam.vp, add_vector(
				mult_vec_double(s->cam.vix, (double)i),
				mult_vec_double(s->cam.viy, (double)j)));
	v = sub_vec_by_vec(vpp, s->cam.c);
	normalize_vector(&v);
	return (v);
}

t_color					get_inters(t_mlx *s, t_vector *v)
{
	int					i;
	double				d;
	double				*res;
	t_object			*closest;

	d = 99999999.9f;
	i = 0;
	closest = NULL;
	while (i < (s->obj_len))
	{
		res = s->objects[i].inter(s->objects[i], v, s->cam.c);
		if (is_closest(&d, res) == 1)
			closest = &s->objects[i];
		free(res);
		i++;
	}
	return ((closest && d < 99999999.9f) ?
			get_color(s, closest,
				add_vector(s->cam.c, mult_vec_double(*v, d))) :
			create_color("0,0,0"));
}

void                render_pic(t_mlx *s)
{
	int                i;
	int                j;
	t_color            tmp;
	t_vector        v;

	j = 0;
	while (j < (WIN_MAX_Y + 1))
	{
		i = 0;
		while (i < (WIN_MAX_X + 1))
		{
			v = create_vector(s, i, j);
			tmp = get_inters(s, &v);
			put_in_image(s, i, j, tmp);
			++i;
		}
		++j;
	}
