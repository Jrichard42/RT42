/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:07:10 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/30 14:07:13 by jqueyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUT_H
# define CUT_H
# include "quadratic.h"
# include "rt.h"
# include "obj.h"

float	cut_cylinder(t_obj *obj, t_ray *ray, t_quadratic *var);
float	cut_cone(t_obj *obj, t_ray *ray, t_quadratic *var);
float	cut_sphere(t_obj *obj, t_ray *ray, t_quadratic *var);

#endif
