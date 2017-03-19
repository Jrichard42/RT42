/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 14:17:41 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/19 11:09:14 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "rt.h"
# include "quadratic.h"
# include "ft_kvlexer.h"

typedef struct	s_cylinder
{
	float		radius;
	t_vector3f 	dir;
}				t_cylinder;

int				create_cylinder(t_kvlexer *token, t_rt *rt);

#endif
