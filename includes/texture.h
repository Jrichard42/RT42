/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:18:41 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/13 16:09:33 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "rt.h"
# include "libft_matrix.h"
#include "bruit_perlin.h"

typedef struct	s_damier
{
	t_vector3f	color_1;
	t_vector3f	color_2;
}				t_damier;

/*typedef struct	s_perlin
{
	double		turbpower;
	double		turbsize;
	t_vector2f	periode;
	t_vector3f	color;
	char		*type_perlin;
}				t_perlin;*/

typedef struct 	s_texture
{
	int 		width;
	int 		height;
	t_vector3f	**data;
}				t_tex;

t_tex		create_texture(const int w, const int h, const char *type);
t_vector3f	get_tex_point(t_tex tex, float u, float v);

#endif
