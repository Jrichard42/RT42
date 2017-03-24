/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:42:45 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/24 17:38:06 by dbreton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# include "ray.h"
# include "material.h"
# include "light.h"
# include "inter.h"
#include "texture.h"

typedef struct s_light	t_light;

typedef	struct			s_obj
{
	t_vector3f			pos;
	t_material			mat;
	int					id;
	int					is_src;
	int					is_visible;
	t_light				light;
	void				*data;
	t_tex				tex;
	float				(*inter)(struct s_obj *, t_ray *);
	t_vector3f			(*normal)(struct s_obj *, t_vector3f *);
	t_vector3f			(*texture)(struct s_obj *, t_inter);
}						t_obj;

#endif
