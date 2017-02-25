/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 14:17:41 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/18 18:24:46 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define light_H

# include "rt.h"
# include "obj.h"
# include "inter.h"
# include "ft_kvlexer.h"

typedef struct	s_light
{
	t_vector3f	color;
}				t_light;

int				create_light(t_kvlexer *token, t_rt *rt);
t_vector3f		calcul_light(t_obj *obj, t_inter *inter, t_ray *ray,
		t_vector3f *color);

#endif
