/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 15:32:43 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/20 15:32:44 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFLEXION_H
# define REFLEXION_H

# include "rt.h"
# include "inter.h"
# include "ray.h"

t_vector3f	apply_reflexion(t_obj *obj,
										t_ray ray,
										int rec_count,
										t_rt *rt);

#endif
