/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetraedre.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 17:51:34 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/08 17:51:36 by jqueyrou         ###   ########.fr       */
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

#endif
