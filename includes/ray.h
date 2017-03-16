/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:38:06 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/18 18:25:27 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

#include "libft_matrix.h"

typedef	struct	s_ray 
{
	t_vector3f	start;
	t_vector3f	dir;
	float		ir;
}				t_ray;

#endif