/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2d.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <jrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 14:36:23 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/12 19:24:58 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR2D_H
# define FT_VECTOR2D_H

typedef struct	s_vector2d
{
  double		x;
  double		y;
}				t_vector2d;

t_vector2d		create_vector2d(double x, double y);
t_vector2d		add_vector2d(t_vector2d v1, t_vector2d v2);
t_vector2d		sub_vector2d(t_vector2d v1, t_vector2d v2);
t_vector2d		mult_vector2d(t_vector2d v1, float nb);
t_vector2d		div_vector2d(t_vector2d v1, float nb);
double			dot_vector2d(t_vector2d v1, t_vector2d v2);
t_vector2d		normalize_vector2d(t_vector2d v1);
float			length_vector2d(t_vector2d v1);

#endif
