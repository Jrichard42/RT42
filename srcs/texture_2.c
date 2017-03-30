/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 19:49:27 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/30 19:49:28 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "parser.h"
#include "bruit_perlin.h"
#include "libft.h"

int							malloc_tex(t_texture *tex)
{
	int y;

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
