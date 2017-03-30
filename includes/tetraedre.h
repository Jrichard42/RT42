/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetraedre.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 17:51:34 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/19 11:46:15 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETRAEDRE_H
# define TETRAEDRE_H

# include "equation.h"
# include "rt.h"
# include "obj.h"
# include "ft_kvlexer.h"
# include "parser.h"
# include "libft.h"
# include "triangle.h"

typedef struct	s_tetra
{
	t_triangle	*face;
}				t_tetra;
int				create_tetra(t_kvlexer *token, t_rt *rt);
void			calc_normal_tetra(t_tetra *tetra);
float			inter_triangles(t_triangle *t, t_ray *ray);
int				create_tetra3(t_kvlexer *token, t_obj *obj);
t_triangle		*create_tetra_bis(t_vector3f v1, t_vector3f v2,
					t_vector3f v3, t_vector3f v4);

#endif
