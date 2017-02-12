/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 12:33:26 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/10 19:04:48 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATRIX_H
# define FT_MATRIX_H

# include "ft_vectors.h"

typedef struct s_vector3f	t_vector3f;

typedef struct	s_matrix
{
	float		tab[4][4];
}				t_matrix;

t_matrix		create_matrix();
t_matrix		mult_matrix(t_matrix *m1, t_matrix *m2);
void			init_identity(t_matrix *matrix);
t_matrix		translation_matrix(t_matrix *transf, t_vector3f vector);
t_matrix		scale_matrix(t_matrix *transf, t_vector3f vector);
t_matrix		rotation_x_matrix(t_matrix *transf, float angle);
t_matrix		rotation_y_matrix(t_matrix *transf, float angle);
t_matrix		rotation_z_matrix(t_matrix *transf, float angle);
#endif
