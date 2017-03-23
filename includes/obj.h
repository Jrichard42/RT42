/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:42:45 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/23 14:13:28 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# include "ray.h"
# include "material.h"
# include "light.h"

typedef struct s_light t_light;

typedef	struct	s_obj
{
	t_vector3f	pos;
	t_material	mat;
	int			id;
	int			is_src;
	int			is_visible;
	t_vector3f	color;
	t_light		light;
	void		*data;
	float		(*inter)(struct s_obj *, t_ray *);
	t_vector3f	(*normal)(struct s_obj *, t_vector3f *);
}				t_obj;

#endif
