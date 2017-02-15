/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 14:17:41 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/09 14:19:05 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "obj.h"
# include "quadratic.h"

typedef struct	s_cylinder
{
	int			radius;
	t_vector3f 	dir;
}				t_cylinder;

t_obj			*create_cylinder(t_kvlexer *token, t_rt *rt);

#endif
