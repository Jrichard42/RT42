/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bruit_perlin.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 15:26:47 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/10 15:26:48 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRUIT_PERLIN_H
# define BRUIT_PERLIN_H
# include "camera.h"
# include "libft_matrix.h"
# include "libft.h"

typedef	struct	s_perlin
{
	t_vector3f	color1;
	t_vector3f	color2;
	t_vector3f	color3;
}				t_perlin;

t_vector3f		bruit_perlin(t_vector2f pixel, char *type);
unsigned int	marble(t_vector2f pixel, double noise[WIN_Y][WIN_X]);
unsigned int	wood(t_vector2f pixel, double noise[WIN_Y][WIN_X]);
t_vector3f		hsl_to_rgb(float h, float s, float l);
float			color_hsl(float tmp_color, float tmp1, float tmp2);
t_vector3f		select_texture(char *type, t_vector2f pixel,
							double noise[WIN_Y][WIN_X]);
double			turbulence(double x,
							double y,
							double size,
							double noise[WIN_Y][WIN_X]);

#endif
