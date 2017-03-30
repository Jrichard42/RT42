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
# include <math.h>
# include <stdlib.h>
# include "texture.h"
# include "equation.h"
# include "rt.h"
# include "obj.h"
# include "ft_kvlexer.h"
# include "parser.h"
# include "libft.h"
# include "light.h"
# include "libft_matrix.h"

typedef	struct	s_perlin
{
	t_vector3f	color1;
	t_vector3f	color2;
	t_vector3f	color3;
}				t_perlin;

typedef	struct	s_marble
{
	t_vector2f	period;
	t_vector2f	turb;
}				t_marble;

int				bruit_perlin(t_vector2f size, double ***noise);
t_vector3f		hsl_to_rgb(float h, float s, float l);
void			free_tab(double **noise, t_vector2f size);
float			color_hsl(float tmp_color, float tmp1, float tmp2);
double			turbulence(t_vector2f pixel,
							double size,
							double **noise,
							t_vector2f size_tex);

#endif
