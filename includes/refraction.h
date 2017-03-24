/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 15:43:17 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/20 15:43:18 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFRACTION_H
# define REFRACTION_H

# include "rt.h"
# include "inter.h"
# include "ray.h"

t_vector3f			apply_refraction(t_obj *obj,
										t_ray ray,
										int rec_count,
										t_rt *rt);

#endif
