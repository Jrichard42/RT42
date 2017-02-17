/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 14:17:41 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/17 20:17:00 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "rt.h"
# include "obj.h"
# include "ft_kvlexer.h"

typedef struct	s_sphere
{
	int			radius;
}				t_sphere;

int				create_sphere(t_kvlexer *token, t_rt *rt);

#endif
