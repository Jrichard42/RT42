/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_shape.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 18:48:35 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/29 18:48:36 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_SHAPE_H
# define TEXTURE_SHAPE_H

# include "rt.h"
# include "ft_kvlexer.h"

t_vector3f			plane_tex(t_obj *obj, t_inter inter);
t_vector3f			cone_tex(t_obj *self, t_inter inter);
t_vector3f			sphere_tex(t_obj *self, t_inter inter);

#endif
