/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:18:41 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/13 15:18:43 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "rt.h"

typedef struct	s_damier
{
	t_vector3f	color_1;
	t_vector3f	color_2
}				t_damier;

typedef struct	s_perlin
{
	double		turbpower;
	double		turbsize;
	t_vector2f	periode;
	t_vector3f	color;
	char		*type_perlin;
}				t_perlin;

#endif