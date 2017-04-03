/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 19:49:27 by abitoun           #+#    #+#             */
/*   Updated: 2017/04/03 14:39:58 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "parser.h"
#include "bruit_perlin.h"
#include "libft.h"

t_vector3f		get_tex_point(t_texture tex, float u, float v)
{
	t_vector3f	color;
	int			x;
	int			y;

	if (u < 0.0f)
		x = (int)(((1.0f - ((long int)u - u))) * tex.width);
	else
		x = (int)(u * tex.width);
	if (v < 0.0f)
		y = (int)(((1.0f - ((long int)v - v))) * tex.height);
	else
		y = (int)(v * tex.height);
	color = tex.data[y % tex.height][x % tex.width];
	return (color);
}

void			del_tex(void *data, size_t size)
{
	int			y;
	t_texture	*tex;

	(void)size;
	tex = (t_texture *)data;
	y = 0;
	while (y < tex->height)
	{
		ft_memdel((void **)&(tex->data[y]));
		++y;
	}
	ft_memdel((void **)&tex->data);
}

int				malloc_tex(t_texture *tex)
{
	int			y;

	y = 0;
	if (!(tex->data = malloc(sizeof(t_vector3f *) * tex->height)))
		return (0);
	while (y < tex->height)
	{
		if (!(tex->data[y] = malloc(sizeof(t_vector3f) * tex->width)))
			return (0);
		y++;
	}
	return (1);
}
