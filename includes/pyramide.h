/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramide.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 17:52:10 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/16 13:37:45 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PYRAMIDE_H
# define PYRAMIDE_H

# include "equation.h"
# include "rt.h"
# include "obj.h"
# include "ft_kvlexer.h"
# include "parser.h"
# include "libft.h"
# include "triangle.h"

typedef struct	s_pyra
{
	t_triangle	*face;
}				t_pyra;

typedef struct	s_vertex
{
	t_vector3f	sommet;
	t_vector3f	v1;
	t_vector3f	v2;
	t_vector3f	v3;
	t_vector3f	v4;
}				t_vertex;
int				create_pyra(t_kvlexer *token, t_rt *rt);
void			calc_normal_pyra(t_pyra *pyra);

#endif
