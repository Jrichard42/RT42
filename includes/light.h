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
# define LIGHT_H

# include "rt.h"
# include "obj.h"
# include "inter.h"
# include "ft_kvlexer.h"

typedef struct	s_light
{
	t_vector3f	color;
	float		intensity;
}				t_light;

int				create_light(t_kvlexer *token, t_rt *rt);
t_vector3f		calcul_light(t_inter *inter, double *coeffs, t_obj *obj);
float			calcul_coef(t_obj *obj, t_inter *inter, t_ray *ray);
void			cap_light(t_vector3f *color);
t_vector3f		calcul_light_procedurale(t_inter *inter, double *coeffs, t_obj *obj);
float			diffuse_light(t_obj *obj, t_inter *inter);
t_vector3f		calcul_light_reflexion(t_list *node, t_inter *inter, t_obj *obj, t_ray *ray);

#endif
