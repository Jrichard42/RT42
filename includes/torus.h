/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 15:52:05 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/02 15:52:11 by jqueyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TORUS_H
# define TORUS_H

# include "equation.h"
# include "rt.h"
# include "obj.h"
# include "ft_kvlexer.h"
# include "parser.h"
# include "libft.h"

typedef struct	s_torus
{
	float		inner_rad;
	float		outer_rad;
	t_vector3f	axis;
}				t_torus;

typedef struct	s_var_torus
{
	float		center_to_ray_dot_dir;
	float		center_to_ray_start_dot_dir_sqrt;
	double		inner_rad_sq;
	double		outer_rad_sq;
	float		axis_dot_centertoray;
	float		axis_dot_raydir;
	double		a;
	double		b;
	double		c;
	double		d;
}				t_var_torus;

int				create_torus(t_kvlexer *token, t_rt *rt);

#endif
