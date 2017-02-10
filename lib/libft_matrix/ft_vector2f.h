/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2f.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <jrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 14:36:23 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/10 19:04:31 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR2F_H
# define FT_VECTOR2F_H

typedef struct	s_vector2f
{
	float		x;
	float		y;
}				t_vector2f;

t_vector2f		create_vector2f(float x, float y);
t_vector2f		add_vector2f(t_vector2f v1, t_vector2f v2);
t_vector2f		sub_vector2f(t_vector2f v1, t_vector2f v2);
t_vector2f		mult_vector2f(t_vector2f v1, float nb);
t_vector2f		div_vector2f(t_vector2f v1, float nb);
float			dot_vector2f(t_vector2f v1, t_vector2f v2);
t_vector2f		normalize_vector2f(t_vector2f v1);
float			length_vector2f(t_vector2f v1);

#endif
